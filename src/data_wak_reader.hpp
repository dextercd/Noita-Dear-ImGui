#ifndef NOITA_IMGUI_DATA_WAK_READER_HPP
#define NOITA_IMGUI_DATA_WAK_READER_HPP

#include <fstream>
#include <optional>
#include <string>
#include <filesystem>
#include <unordered_map>

struct DataWakEntry {
    std::uint32_t offset;
    std::uint32_t size;
};

class DataWakReader {
private:
    std::ifstream wakfile;

    std::unordered_map<std::filesystem::path, DataWakEntry> file_entries;
    std::uint32_t file_table_end;

public:
    DataWakReader(const char* path);
    std::optional<std::string> get_file(const std::filesystem::path& target);

private:
    std::uint32_t read_le_u32(std::uint32_t offset);
    std::uint32_t read_le_u32_here();
};

#endif // Header guard
