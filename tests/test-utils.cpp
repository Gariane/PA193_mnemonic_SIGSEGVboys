#include "catch.hpp"
#include <string>
#include <sstream>
#include "dictionary.hpp"


TEST_CASE("BIP39::Dictionary - invalid path") {
    const std::string path("/path/that/hopefully/doesnt/exist");
    REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::invalid_argument);
}

TEST_CASE("BIP39::Dictionary - ASCII files") {
    // "../" because this is ran from build/ directory in CI
    BIP39::Dictionary dict("../wordlists/english.txt");
    SECTION("Index to word and back") {
        for (int i = 0; i < 2048; i++) {
            std::wstring current;
            CHECK_NOTHROW(current = dict.getWord(i));
            REQUIRE(dict.getIndex(current) == i);
        }
    }
}

TEST_CASE("DICTIONARY-CZECH") {
    const std::string path("../wordlists/czech.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-ENGLISH") {
    const std::string path("../wordlists/english.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-FRENCH") {
    const std::string path("../wordlists/french.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-CHINESE-SIMPLIFIED") {
    const std::string path("../wordlists/chinese_simplified.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-TRADITIONAL") {
    const std::string path("../wordlists/chinese_traditional.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-ITALIAN") {
    const std::string path("../wordlists/italian.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-JAPANESE") {
    const std::string path("../wordlists/japanese.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-KOREAN") {
    const std::string path("../wordlists/korean.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}

TEST_CASE("DICTIONARY-SPANISH") {
    const std::string path("../wordlists/spanish.txt");
    REQUIRE_NOTHROW(BIP39::Dictionary(path));
}
