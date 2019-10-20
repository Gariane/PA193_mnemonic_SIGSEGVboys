#include <algorithm>

#include "catch.hpp"
#include "mnemonic.hpp"
#include "dictionary.hpp"
#include "data/officialTestVectors.hpp"

using BIP39::Mnemonic;
using BIP39::Dictionary;

bool operator==(const std::vector<std::string>& phrase1, const std::vector<std::string>& phrase2) {
    return std::equal(phrase1.begin(), phrase1.end(), phrase2.end());
}

TEST_CASE("OFFICIAL TEST VECTORS") {

   for (size_t i = 0; i < officialTestVectors.size(); ++i) { 
        auto dict = Dictionary("../wordlists/english.txt");

        const testData& t = officialTestVectors[i];

        DYNAMIC_SECTION("Generation from entropy" << i) {
            auto mnemonic = Mnemonic(t.entropy, dict);    

            CHECK(mnemonic.getEntropy() == t.entropy);
            CHECK(mnemonic.getSeed() == t.seed);
            CHECK(mnemonic.getPhrase() == t.phrase);
        }

        DYNAMIC_SECTION("Generation from phrase " << i) {
            auto mnemonic = Mnemonic(t.phrase, dict); 

            CHECK(mnemonic.getEntropy() == t.entropy);
            CHECK(mnemonic.getSeed() == t.seed);
            CHECK(mnemonic.getPhrase() == t.phrase);
        }

        DYNAMIC_SECTION("Phrase-Seed pair" << i) {
            CHECK(Mnemonic::checkPhraseSeedPair(t.phrase, t.seed, dict));
        }

   } 

}
