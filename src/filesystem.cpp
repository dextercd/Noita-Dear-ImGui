#include <algorithm>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <iostream>

#include <shlobj.h>
#include <shellapi.h>

#include <tinyxml2.h>

#include "filesystem.hpp"
#include "data_wak_reader.hpp"

namespace fs = std::filesystem;

struct ModLayer {
    fs::path mod_path;
    fs::path directory;
};

std::optional<std::string> read_full_file(const fs::path& file_path)
{
    std::ifstream ifs{file_path, std::ios_base::binary};
    if (!ifs)
        return std::nullopt;

    std::string content;

    ifs.seekg(0, std::ios::end);
    content.resize(ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    ifs.read(content.data(), content.size());

    return content;
}

bool is_mods_dir(const fs::path& path)
{
    static const fs::path mods_dir = "mods";
    return std::mismatch(
        std::begin(mods_dir), std::end(mods_dir),
        std::begin(path), std::end(path)
    ).first == std::end(mods_dir);
}

bool is_data_dir(const fs::path& path)
{
    static const fs::path data_dir = "data";
    return std::mismatch(
        std::begin(data_dir), std::end(data_dir),
        std::begin(path), std::end(path)
    ).first == std::end(data_dir);
}

struct FileSystem : IFileSystem {
    std::vector<ModLayer> mod_layers;
    std::optional<DataWakReader> wak_reader;
    fs::path working_dir;

    std::optional<std::string> find_mod_file(const fs::path& path)
    {
        for (auto&& mod : mod_layers) {
            auto mod_match = std::mismatch(
                std::begin(mod.mod_path), std::end(mod.mod_path),
                std::begin(path), std::end(path));

            if (mod_match.first != std::end(mod.mod_path))
                continue;

            auto modrel_path = fs::path();
            std::for_each(mod_match.second, std::end(path),
                [&](auto& p) { modrel_path /= p; });
            auto file_path = mod.directory / modrel_path;

            if (auto content = read_full_file(file_path); content)
                return content;
        }

        return std::nullopt;
    }

    std::optional<std::string> get_file(const fs::path& path_) override
    {
        auto path = path_.lexically_normal();
        if (path.is_absolute())
            return std::nullopt;

        static const fs::path dotdot = "..";
        if (std::find(std::begin(path), std::end(path), dotdot) != std::end(path))
            return std::nullopt;

        if (is_mods_dir(path)) {
            if (auto mod_content = find_mod_file(path); mod_content)
                return mod_content;
        } else if (is_data_dir(path)) {
            for (auto&& mod : mod_layers) {
                // Try mods/<mod_id>/data/xyz.png
                if (auto content = read_full_file(mod.directory / path); content)
                    return content;
            }

            if (wak_reader) {
                if (auto wak_result = wak_reader->get_file(path); wak_result)
                    return wak_result;
            }
        }

        return read_full_file(working_dir / path);
    }
};

std::vector<ModLayer> get_mod_layers(const fs::path& modconfig_path)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(modconfig_path.string().c_str())) {
        std::cerr << "Couldn't read mod config file " << modconfig_path << '\n';
        return {};
    }

    std::vector<ModLayer> mod_layers;

    auto mods_list = doc.RootElement();
    for (auto mod_entry = mods_list->LastChildElement("Mod");
         mod_entry;
         mod_entry = mod_entry->PreviousSiblingElement("Mod"))
    {
        if (mod_entry->IntAttribute("enabled") == 0)
            continue;

        auto name = mod_entry->Attribute("name");
        auto workshop_id = mod_entry->Int64Attribute("workshop_item_id");

        auto mod_path = fs::path{"mods"} / name;

        if (workshop_id == 0) {
            mod_layers.push_back({
                .mod_path = mod_path,
                .directory = fs::absolute(mod_path),
            });
        } else {
            mod_layers.push_back({
                .mod_path = mod_path,
                .directory = fs::absolute(
                    fs::path{"../../workshop/content/881100"}
                        / std::to_string(workshop_id)),
            });
        }
    }

    return mod_layers;
}

FileSystem construct_fs(const fs::path& modconfig_path)
{
    FileSystem filesystem;

    filesystem.mod_layers = get_mod_layers(modconfig_path);
    filesystem.working_dir = fs::current_path();

    if (fs::exists("data/data.wak")) {
        filesystem.wak_reader = DataWakReader{"data/data.wak"};
    };

    return filesystem;
}

std::wstring get_nolla_appdata_path()
{
    auto co_free = [](void* ptr) { CoTaskMemFree(ptr); };
    std::unique_ptr<wchar_t[], decltype(co_free)> locallow_path;

    wchar_t* locallow_path_ret{};
    SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, KF_FLAG_CREATE, nullptr, &locallow_path_ret);
    locallow_path.reset(locallow_path_ret);

    std::wstring path{locallow_path.get()};
    path += L"\\Nolla_Games_Noita";

    return path;
}

std::unique_ptr<FileSystem> current_fs;

enum class save_location {
    local,
    appdata,
};

IFileSystem& get_fs()
{
    if (!current_fs) {
        save_location save_loc = save_location::appdata;

        int arg_count;
        wchar_t** arg_list = CommandLineToArgvW(GetCommandLineW(), &arg_count);
        if(arg_list) {
            // Noita dev has a different default
            if (std::wstring_view{arg_list[0]}.ends_with(L"noita_dev.exe"))
                save_loc = save_location::local;

            // Command line flags that overwrite the default
            for (int i = 1; i < arg_count; ++i) {
                auto option = std::wstring_view{arg_list[i]};
                if (option == L"-always_store_userdata_in_appdata")
                    save_loc = save_location::appdata;
            }
            for (int i = 1; i < arg_count; ++i) {
                auto option = std::wstring_view{arg_list[i]};
                if (option == L"-always_store_userdata_in_workdir")
                    save_loc = save_location::local;
            }

            LocalFree(arg_list);
        }

        std::wstring save_path = L".";
        if (save_loc == save_location::appdata)
            save_path = get_nolla_appdata_path();

        current_fs = std::make_unique<FileSystem>(
            construct_fs(save_path + L"\\save00\\mod_config.xml"));
    }

    return *current_fs;
}
