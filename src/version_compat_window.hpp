enum incompatibility_reason {
    cant_parse_version,
    version_mismatch,
};

void show_version_compat_window();
void report_incompatibility(std::string mod_name, std::string version, incompatibility_reason reason);
