#include "catch.hpp"
#include <string>
#include <sstream>
#include "dictionary.hpp"


void indexAndBack(BIP39::Dictionary& dict) {
    for (int i = 0; i < 2048; i++) {
        std::wstring current;
        CHECK_NOTHROW(current = dict.getWord(i));
        REQUIRE(dict.getIndex(current) == i);
    }
    REQUIRE_THROWS_AS(dict.getIndex(L"totallyNonExistentButValidWordNotPresentInTheDictionary"), std::out_of_range);
    REQUIRE_THROWS_AS(dict.getWord(-1), std::out_of_range);
    REQUIRE_THROWS_AS(dict.getWord(2049), std::out_of_range);
}

TEST_CASE("BIP39::Dictionary - invalid path") {
    const std::string path("/path/that/hopefully/doesnt/exist");
    REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::invalid_argument);
}

TEST_CASE("BIP39::Dictionary - Invalid files") {
    SECTION("> 2048 words") {
        const std::string path("../wordlists/test_wordlists/es-morew.txt");
        REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::length_error);
    }
    SECTION("< 2048 words") {
        const std::string path("../wordlists/test_wordlists/es-lessw.txt");
        REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::length_error);
    }
    SECTION("Whitespaces in words") {
        const std::string path("../wordlists/test_wordlists/es-whitespace.txt");
        REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::invalid_argument);
    }
    SECTION("Trailing newline") {
        const std::string path("../wordlists/test_wordlists/es-trendl.txt");
        REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::length_error);
    }
    SECTION("Blank line") {
        const std::string path("../wordlists/test_wordlists/es-blankline.txt");
        REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::invalid_argument);
    }
}

TEST_CASE("DICTIONARY-CZECH") {
    const std::string path("../wordlists/czech.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-ENGLISH") {
    const std::string path("../wordlists/english.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-FRENCH") {
    const std::string path("../wordlists/french.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-CHINESE-SIMPLIFIED") {
    const std::string path("../wordlists/chinese_simplified.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-TRADITIONAL") {
    const std::string path("../wordlists/chinese_traditional.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-ITALIAN") {
    const std::string path("../wordlists/italian.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-JAPANESE") {
    const std::string path("../wordlists/japanese.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-KOREAN") {
    const std::string path("../wordlists/korean.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}

TEST_CASE("DICTIONARY-SPANISH") {
    const std::string path("../wordlists/spanish.txt");
    BIP39::Dictionary dict(path);
    SECTION("Index to word and back") {
        indexAndBack(dict);
    }
}
