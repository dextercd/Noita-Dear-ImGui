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

    auto file_count = read_le_u32(header_file_count);
    file_table_end = read_le_u32(header_header_and_table_size);

    file_entries.reserve(file_count);

    wakfile.seekg(file_table_start, std::ios_base::beg);
    while (wakfile.tellg() < file_table_end) {
        auto file_offset = read_le_u32_here();
        auto file_size = read_le_u32_here();
        auto name_size = read_le_u32_here();

        std::string file_name;
        file_name.resize(name_size);
        wakfile.read(file_name.data(), file_name.size());

        file_entries.insert({
            std::move(file_name),
            DataWakEntry{.offset=file_offset, .size=file_size}
        });
    }
}

std::optional<std::string> DataWakReader::get_file(const fs::path& target)
{
    auto f = file_entries.find(target);
    if (f == std::end(file_entries))
        return std::nullopt;

    wakfile.seekg(f->second.offset, std::ios_base::beg);
    std::string file_content;
    file_content.resize(f->second.size);
    wakfile.read(file_content.data(), file_content.size());

    return file_content;
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
