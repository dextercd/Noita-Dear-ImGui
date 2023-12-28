#ifndef NOITA_IMGUI_FILESYSTEM_HPP
#define NOITA_IMGUI_FILESYSTEM_HPP

#include <filesystem>
#include <optional>
#include <string>

struct IFileSystem {
    virtual std::optional<std::string> get_file(const std::filesystem::path&)=0;
};

std::wstring get_nolla_appdata_path();
IFileSystem& get_fs();

#endif // Header guard
