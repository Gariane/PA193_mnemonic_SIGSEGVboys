#include "catch.hpp"
#include <string>
#include "dictionary.hpp"


TEST_CASE("BIP39::Dictionary - invalid path") {
    const std::string path("/path/that/hopefully/doesnt/exist");
    REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::invalid_argument);
}

TEST_CASE("BIP39::Dictionary - ASCII files") {
    BIP39::Dictionary dict("wordlists/english.txt");
    SECTION("Index to word and back") {
        for (int i = 0; i < 2048; i++) {
            std::wstring current;
            CHECK_NOTHROW(current = dict.getWord(i));
            REQUIRE(dict.getIndex(current) == i);
        }
    }
}
