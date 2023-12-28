#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
#include <filesystem>

#include "data_wak_reader.hpp"

namespace fs = std::filesystem;

constexpr std::size_t header_file_count = 4;
constexpr std::size_t header_header_and_table_size = 8;
constexpr std::size_t file_table_start = 16;

DataWakReader::DataWakReader(const char* path)
    : wakfile{path, std::ios_base::binary}
{
    wakfile.exceptions(std::ifstream::failbit);

    file_count = read_le_u32(header_file_count);
    file_table_end = read_le_u32(header_header_and_table_size);
}

std::optional<std::string> DataWakReader::get_file(const fs::path& target)
{
    wakfile.seekg(file_table_start, std::ios_base::beg);

    auto target_size = target.string().size();

    std::string curr_filename;
    curr_filename.resize(target_size);

    while (wakfile.tellg() < file_table_end) {
        auto file_offset = read_le_u32_here();
        auto file_size = read_le_u32_here();
        auto name_size = read_le_u32_here();
        if (name_size != target_size) {
            wakfile.seekg(name_size, std::ios_base::cur);
            continue;
        }

        wakfile.read(curr_filename.data(), curr_filename.size());
        if (curr_filename != target)
            continue;

        wakfile.seekg(file_offset, std::ios_base::beg);
        std::string file_content;
        file_content.resize(file_size);
        wakfile.read(file_content.data(), file_content.size());

        return file_content;
    }

    return std::nullopt;
}

std::uint32_t DataWakReader::read_le_u32(std::uint32_t offset)
{
    wakfile.seekg(offset, std::ios_base::beg);
    return read_le_u32_here();
}

std::uint32_t DataWakReader::read_le_u32_here()
{
    char data[4]{};
    wakfile.read(data, 4);
    return
        (std::uint32_t)(unsigned char)data[0] |
        (std::uint32_t)(unsigned char)data[1] << 8 |
        (std::uint32_t)(unsigned char)data[2] << 16 |
        (std::uint32_t)(unsigned char)data[3] << 24;
}

std::string DataWakReader::read_string(std::uint32_t offset)
{
    auto size = read_le_u32(offset);
    std::string str;
    str.resize(size);
    wakfile.read(str.data(), str.size());
    return str;
}
