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
        auto mnemonic = Mnemonic("00000000000000000000000000000000", "", dict);    

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

    SECTION("Generation from phrase - bad words in mnemonic sentence") {
        CHECK_THROWS_AS(Mnemonic("velmi zle slovo", "112", dict, Mnemonic::fromPhrase::Phrase), std::invalid_argument); 
    }

    SECTION("Phrase-Seed pair - bad words in mnemonic sentence") {
        CHECK_THROWS_AS(Mnemonic::checkPhraseSeedPair("avokado", "badSeed", "qweqwe", dict), std::invalid_argument);
    }
}

TEST_CASE("INVALID TESTS WITH MNEMONIC EXCEPTIONS") { 
    auto dict = Dictionary("../wordlists/english.txt");

    SECTION("ENTROPY TOO SHORT") {
        CHECK_THROWS_AS(Mnemonic("", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("", "asd", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c", "asd", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4", "asd", dict), std::invalid_argument);
    }
    SECTION("ENTROPY TOO LONG") {
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5", "xd", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d51a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d51a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5", "xd", dict), std::invalid_argument);
    }
    SECTION("ENTROPY NOT MULTIPLE OF 32 BITS") {
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5aa", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5aa", "dummy", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5aabcd", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5aabcd", "dummy", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5aabcd123c", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d5aabcd123c", "dummy", dict), std::invalid_argument);
    }
    SECTION("ENTROPY NOT HEX STRING") {
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3cXD", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3cXD", "dummy", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1HHHHHHHHHHb3c4d5e6f1a2b3c4d5e6f1a2b3c12", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1HHHHHHHHHHb3c4d5e6f1a2b3c4d5e6f1a2b3c12", "dummy", dict), std::invalid_argument);
    }

    SECTION("PHRASE CONSTRUCTION CHECKSUM NOT VALID") {
        CHECK_THROWS_AS(Mnemonic("legal winner thank year wave sausage worth useful legal winner thank abandon", "", dict, Mnemonic::fromPhrase::Phrase), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("legal winner thank year wave sausage worth useful legal winner thank abandon", "dummyPASS", dict, Mnemonic::fromPhrase::Phrase), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("all hour make first leader extend hole alien behind guard gospel lava path output census museum junior mass reopen famous sing advance salt winner", "", dict, Mnemonic::fromPhrase::Phrase), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic("all hour make first leader extend hole alien behind guard gospel lava path output census museum junior mass reopen famous sing advance salt winner", "dummyPASS", dict, Mnemonic::fromPhrase::Phrase), std::invalid_argument);
    }
    
    SECTION("PHRASE-SEED CHECKSUM NOT VALID") {
        CHECK_THROWS_AS(Mnemonic::checkPhraseSeedPair("legal winner thank year wave sausage worth useful legal winner thank abandon", "", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic::checkPhraseSeedPair("legal winner thank year wave sausage worth useful legal winner thank abandon", "dummySEED", "dummyPASS", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic::checkPhraseSeedPair("all hour make first leader extend hole alien behind guard gospel lava path output census museum junior mass reopen famous sing advance salt winner", "", "", dict), std::invalid_argument);
        CHECK_THROWS_AS(Mnemonic::checkPhraseSeedPair("all hour make first leader extend hole alien behind guard gospel lava path output census museum junior mass reopen famous sing advance salt winner", "dummySEED", "dummyPASS", dict), std::invalid_argument);
    }

	/*New tests for bin format*/
	SECTION("BIN ENTROPY TOO SHORT") {
		CHECK_THROWS_AS(Mnemonic("", "", dict, BIP39::Mnemonic::fromEntropy::BinaryEntropy), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("01111100", "asd", dict, BIP39::Mnemonic::fromEntropy::BinaryEntropy), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("001110001010", "", dict, BIP39::Mnemonic::fromEntropy::BinaryEntropy), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("01110000101010101", "asd", dict, BIP39::Mnemonic::fromEntropy::BinaryEntropy), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("11111111111111111111111111100000000001111111111", "", dict, BIP39::Mnemonic::fromEntropy::BinaryEntropy), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("11111111111111111111111000000000000000000011111", "asd", dict, BIP39::Mnemonic::fromEntropy::BinaryEntropy), std::invalid_argument);
	}
	SECTION("BIN ENTROPY TOO LONG") {
		CHECK_THROWS_AS(Mnemonic("11111111111111111111000000000000010100000000000011000101010101010101111111111111111111100000000000000000000000001010010101010101010101010101010101010101010101010101011010101010000000000000000000000000001111111111111111111111111111111100000000000000000000000111111111", "", dict), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("00000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", "xd", dict), std::invalid_argument);
	}
	SECTION("BIN ENTROPY NOT MULTIPLE OF 32 BITS") {
		CHECK_THROWS_AS(Mnemonic("0000000000000000000000000100000000000000000000000000000000000000000011100000000000000000000000000000000000000000000000000000000011111111", "", dict), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("000000000000000000000000010000101010101010101010101010101010100000000000000000000000000000000000000011100000000000000000000000000000000000000000000000000000000011111111", "dummy", dict), std::invalid_argument);
	}
	SECTION("BIN ENTROPY NOT BIN STRING") {
		CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3cXD", "", dict), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1a2b3c4d1a2b3c4d5e6f1a2b3c4d5e6f1a2b3cXD", "dummy", dict), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1HHHHHHHHHHb3c4d5e6f1a2b3c4d5e6f1a2b3c12", "", dict), std::invalid_argument);
		CHECK_THROWS_AS(Mnemonic("1a2b3c4d5e6f1a2b3c4d5e6f1HHHHHHHHHHb3c4d5e6f1a2b3c4d5e6f1a2b3c12", "dummy", dict), std::invalid_argument);
	}
}


