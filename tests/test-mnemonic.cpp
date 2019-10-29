#include <algorithm>

#include "catch.hpp"
#include "mnemonic.hpp"
#include "dictionary.hpp"
#include "data/officialTestVectors.hpp"

using BIP39::Mnemonic;
using BIP39::Dictionary;

namespace {

void runTests(const std::vector<testData>& data, const Dictionary& dict) {
   for (size_t i = 0; i < data.size(); ++i) { 
        const testData& t = officialTestVectors[i];

        DYNAMIC_SECTION("Generation from entropy " << i) {
            auto mnemonic = Mnemonic(t.entropy, t.passphrase, dict);    

            CHECK(mnemonic.getEntropy() == t.entropy);
            CHECK(mnemonic.getSeed() == t.seed);
            CHECK(mnemonic.getPhrase() == t.phrase);
        }

        DYNAMIC_SECTION("Generation from phrase " << i) {
            auto mnemonic = Mnemonic(t.phrase, t.passphrase, dict); 

            CHECK(mnemonic.getEntropy() == t.entropy);
            CHECK(mnemonic.getSeed() == t.seed);
            CHECK(mnemonic.getPhrase() == t.phrase);
        }

        DYNAMIC_SECTION("Phrase-Seed pair " << i) {
            CHECK(Mnemonic::checkPhraseSeedPair(t.phrase, t.seed, t.passphrase, dict));
        }

   } 
}

} // end anonymous namespace

TEST_CASE("OFFICIAL TEST VECTORS") {
    runTests(officialTestVectors, Dictionary("../wordlists/english.txt"));
}
