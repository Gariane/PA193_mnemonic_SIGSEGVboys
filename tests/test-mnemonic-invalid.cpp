#include <stdexcept>

#include "catch.hpp"
#include "mnemonic.hpp"
#include "dictionary.hpp"
#include "data/testData.hpp"

using BIP39::Mnemonic;
using BIP39::Dictionary;

TEST_CASE("INVALID TESTS WITHOUT EXCEPTIONS") {
    auto dict = Dictionary("../wordlists/english.txt");


    SECTION("Generation from entropy ") {
        auto mnemonic = Mnemonic("0000000000000000000000000000000", "", dict);    

        CHECK(mnemonic.getEntropy() != "pepek namornik 123 spenat");
        CHECK(mnemonic.getSeed() != "SIGSEGV bois");
        CHECK(mnemonic.getPhrase() != "abandon abandon abort");
    }

    SECTION("Generation from phrase ") {
        auto mnemonic = Mnemonic("letter advice cage absurd amount doctor acoustic avoid letter advice cage above", "112", dict, Mnemonic::fromPhrase::Phrase); 

        CHECK(mnemonic.getEntropy() != "badEntropy");
        CHECK(mnemonic.getSeed() != "badSeed");
        CHECK(mnemonic.getPhrase() != "badPhrase");
    }

    SECTION("Phrase-Seed pair") {
        CHECK_FALSE(Mnemonic::checkPhraseSeedPair("letter advice cage absurd amount doctor acoustic avoid letter advice cage above", "badSeed", "qweqwe", dict));
    }

}

TEST_CASE("INVALID TESTS WITH DICTIONARY EXCEPTIONS") {
    auto dict = Dictionary("../wordlists/english.txt");

    SECTION("Generation from phrase") {
        CHECK_THROWS_AS(Mnemonic("velmi zle slovo", "112", dict, Mnemonic::fromPhrase::Phrase), std::out_of_range); 
    }

    SECTION("Phrase-Seed pair") {
        CHECK_THROWS_AS(Mnemonic::checkPhraseSeedPair("avokado", "badSeed", "qweqwe", dict), std::out_of_range);
    }

}
