#ifndef NOITA_IMGUI_DATA_WAK_READER_HPP
#define NOITA_IMGUI_DATA_WAK_READER_HPP

#include <fstream>
#include <optional>
#include <string>
#include <filesystem>

struct DataWakReader {
    std::ifstream wakfile;

    std::uint32_t file_count;
    std::uint32_t file_table_end;

    DataWakReader(const char* path);
    std::optional<std::string> get_file(const std::filesystem::path& target);

private:
    std::uint32_t read_le_u32(std::uint32_t offset);
    std::uint32_t read_le_u32_here();
    std::string read_string(std::uint32_t offset);
};

#endif // Header guard
