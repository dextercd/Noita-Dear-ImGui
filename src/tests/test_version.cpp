#include <catch2/catch_test_macros.hpp>

#include "version_number.hpp"

version_number vparse(std::string_view version_str)
{
    auto version = version_number::from_string(version_str);
    REQUIRE(version.has_value());
    return *version;
}

bool is_valid(std::string_view version_str) {
    return version_number::from_string(version_str).has_value();
}

TEST_CASE("Version numbers are parsed correctly", "[version]") {
    REQUIRE(vparse("2.1.0") == version_number{2, 1, 0, -1});
    REQUIRE(vparse("2.1.0.0") == version_number{2, 1, 0, 0});
}

TEST_CASE("Version number comparisons", "[version]") {
    REQUIRE(vparse("2.1.0") > vparse("1.999.999"));
    REQUIRE(vparse("1.1000.0") > vparse("1.999.999"));
}

TEST_CASE("Incorrect version numbers", "[version]") {
    REQUIRE(!is_valid("1.0.0.0.0")); // Too many components

    REQUIRE(!is_valid("1.0.0.0."));
    REQUIRE(!is_valid("1.0.0."));
    REQUIRE(!is_valid("1.0."));

    REQUIRE(!is_valid("43..4"));


    REQUIRE(!is_valid("-1.1.1"));
    REQUIRE(!is_valid("1.-1.1"));
    REQUIRE(!is_valid("1.1.-1"));

    REQUIRE(!is_valid("1,2.3.4"));

    REQUIRE(!is_valid(""));
}

TEST_CASE("Version compatible", "[version]") {
    REQUIRE(version_compatible(vparse("2.3"), vparse("2.3")));
    REQUIRE(version_compatible(vparse("1.0.0"), vparse("1.0.0")));
    REQUIRE(version_compatible(vparse("1.0.0.1"), vparse("1.0.0.1")));

    REQUIRE(version_compatible(vparse("2.3"), vparse("2.0")));
    REQUIRE(!version_compatible(vparse("2.0"), vparse("2.3")));
    REQUIRE(version_compatible(vparse("2"), vparse("2.0")));

    // Difference in major version is always incompatible
    REQUIRE(!version_compatible(vparse("3"), vparse("2.99")));
    REQUIRE(!version_compatible(vparse("3"), vparse("4.99")));

    REQUIRE(version_compatible(vparse("3.9999"), vparse("3")));
    REQUIRE(version_compatible(vparse("3"), vparse("3.9999")));
    REQUIRE(version_compatible(vparse("3.9.999"), vparse("3")));
    REQUIRE(version_compatible(vparse("3"), vparse("3.9.999")));
    REQUIRE(version_compatible(vparse("3.9.9.99"), vparse("3")));
    REQUIRE(version_compatible(vparse("3"), vparse("3.9.9.99")));

    // This is the main usage I have in mind for this. Given that the library
    // is the version on the left, and the mod requests the version on the
    // right, will these be compatible?
    // If a component is not specified then it's assumed that any version there
    // would be fine. (Must at least specify the major version.)
    REQUIRE(version_compatible(vparse("3.12.1.4"), vparse("3")));
    REQUIRE(version_compatible(vparse("3.12.1.4"), vparse("3.11")));
    REQUIRE(version_compatible(vparse("3.12.1.4"), vparse("3.12")));
    REQUIRE(!version_compatible(vparse("3.12.1.4"), vparse("3.13")));
    REQUIRE(version_compatible(vparse("3.12.1.4"), vparse("3.12.1")));
    REQUIRE(version_compatible(vparse("3.12.1.4"), vparse("3.11.6")));
}
