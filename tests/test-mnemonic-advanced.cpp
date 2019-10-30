#include <string>
#include <algorithm>

#include "catch.hpp"
#include "mnemonic.hpp"
#include "dictionary.hpp"
#include "data/testData.hpp"

using BIP39::Mnemonic;
using BIP39::Dictionary;


void checkAll(const Mnemonic& mnemonic, std::string entropy, std::string seed, const std::string& phrase) {
    std::transform(entropy.begin(), entropy.end(), entropy.begin(), [](char c){ return std::tolower(c); });
    std::transform(seed.begin(), seed.end(), seed.begin(), [](char c){ return std::tolower(c); });
    
    CHECK(mnemonic.getEntropy() == entropy);
    CHECK(mnemonic.getSeed() == seed);
    CHECK(mnemonic.getPhrase() == phrase);
}

void checkMnemonic(const std::string& entropy, const std::string& password, const std::string& seed, const std::string& sentence, const Dictionary& dict) {
    auto mnemonic = Mnemonic(entropy, password, dict);
    checkAll(mnemonic, entropy, seed, sentence);
    CHECK(Mnemonic::checkPhraseSeedPair(mnemonic.getPhrase(), mnemonic.getSeed(), password, dict));
    
    mnemonic = Mnemonic(mnemonic.getPhrase(), password, dict, Mnemonic::fromPhrase::Phrase);
    checkAll(mnemonic, entropy, seed, sentence);
    CHECK(Mnemonic::checkPhraseSeedPair(mnemonic.getPhrase(), mnemonic.getSeed(), password, dict));
}

TEST_CASE("VERY COMPLEX PASSWORDS") {
    std::string password1 = "882e8bf3aa347ee387126972a3f1372bVERYCOMPLEXPASSWORDa64dc5bf3624d1ee486833a3c4c578e0";
    std::string password2 = "?TH1S..?;prettyc()mpleX922apas$w%rd11";
    
    std::string entropy = "9b879e2eeeb087c0a9e2a510d5553366";

    
    SECTION("ENGLISH") {
        auto dict = Dictionary("../wordlists/english.txt");
        SECTION("1") {
            checkMnemonic(entropy, password1, "e69f44de8836c4871d9cc3f56c27e3ea64f8309c6689b9487b183b728eaf305565b9135bedb761c6ada7bc0719444586157d6cd4fc281ed2c0d3283bc60b8a8b",
                "oppose diagram merry talent anchor theory pole feed awkward primary error slush",
                dict);
        }
        SECTION("2") {
            checkMnemonic(entropy, password2, "a8c0a3d4c26cfc4bea833bf4fd45754fe3a854067a813475cdc44df241947d01f773077fc60bb8eba52a4da86253cc46fa973835abe942af48b2a9efb7ac4737",
                "oppose diagram merry talent anchor theory pole feed awkward primary error slush",
                dict);
        }
    }

    SECTION("JAPANESE") {
        auto dict = Dictionary("../wordlists/japanese.txt");
        
        SECTION("1") {
            checkMnemonic(entropy, password1, "33923ee9bea3cfda4584cbf537049c89a66907e2a7250ba7af016703cbc8ffdfc9a61ce7578c6790c22b907f8bfc369f11234cc3d2b12e15a3ec387ca426d3f6",
                "つもる くちこみ たとえる ほしい いこう まがる とくべつ こもの いれもの ともる こうつう ひつじゅひん",
                dict);
        }
        SECTION("2") {
            checkMnemonic(entropy, password2, "dffd3eceaf2793a469822d6fbddc5210fe1191e023efcc88bfef7b6a1fffb3d6ccfa9fddd1938223ea59eecb00b22e88656e8f9a902196ddf050a4d02abf1d32",
                "つもる くちこみ たとえる ほしい いこう まがる とくべつ こもの いれもの ともる こうつう ひつじゅひん",
                dict);
        }
    }

    SECTION("SPANISH") {
        auto dict = Dictionary("../wordlists/spanish.txt");

        SECTION("1") {
            checkMnemonic(entropy, password1, "0f4ce42092b122fbdc58e1900c3d30ac4d90e4d964b5efd0b8284b4a3f34cbe99d7eabf498854b1c14dbe9073d7601387bac2f568986a8798658d669a97b692b",
                "nómina culebra medio sultán alegre talón óvulo falda arar papel enero rojizo",
                dict);
        }
        SECTION("2") {
            checkMnemonic(entropy, password2, "312e0900fbb5eb911a2ef0ed514c601e434475bf799892e2dfae0c459bc342bce2811bd2a92d6862cbc362ce5176825728ae1697ce6df69065ecdf208460606f",
                "nómina culebra medio sultán alegre talón óvulo falda arar papel enero rojizo",
                dict);
        }
    }

    SECTION("TRADITIONAL CHINESE") {
        auto dict = Dictionary("../wordlists/chinese_traditional.txt");
        
        SECTION("1") {
            checkMnemonic(entropy, password1, "6bef56d8e262c73104da86ed00fb4a5895c362416b73fb7289f45aa096ee99c526ea1c48f27399fd65a7fdfe7fc43960166aec160c67bb218dfd35b562e88749",
                "薩 照 忽 叔 著 衰 授 微 重 琴 夠 輩",
                dict);
        }
        SECTION("2") {
            checkMnemonic(entropy, password2, "bbd3b13a2c497b33e50ff7a87ad606adf1853178ed90d1ce908c670c5a18d718ff1ae8229a1c3b617a01d75b846b19d8fe67b408b94e717fbfeda050bbdf0762",
                "薩 照 忽 叔 著 衰 授 微 重 琴 夠 輩",
                dict);
        }
    }
}


TEST_CASE("ENTROPY WITH BIG LETTERS") {
    std::string entropy1 = "882E8BF3AA347EE387126972A3F1372B";
    std::string entropy2 = "D2992BBC84C62F265B6EC39466E530C1FF47C70EC54E6874E78910414A070C0C";
    std::string password = "this is password";
    
    auto dict = Dictionary("../wordlists/english.txt");
    
    SECTION("WITH PASSWORD") {
        checkMnemonic(entropy1, password, "8ced03f39fb017719d98c7e58109317959eefc9ee4420037b1e628c2914dac9b9c60385fb0d4542a9bf7bfcbc4d955ca1ead653d8bf6f9309f793072d7de604b",
            "market inmate woman federal elevator impact brisk essay increase buzz evidence fine",
            dict);
        
        checkMnemonic(entropy2, password, "d73f64bcc93f92006cd539b7fd20456fdcef8e28b13e48f5edad4d59796712ec094e24df72b50c86fd16a4d3284aa7cd31a35c1353e4e0ac187d3f709621193d",
            "spoon sing upset another glass nasty horror such nerve damp equip loop virtual toe deposit prefer half poet time calm believe adjust coral lens",
            dict);
    }
    
    SECTION("WITHOUT PASSWORD") {
        checkMnemonic(entropy1, "", "5ef6c88257b54ccd331c5f82c9387b3edbe32da4dfb398684b9bea71befab76b7ac6d7e43205e8748a4ef5d1da513d41f9671b8c36f059c8c9efe0233f6ad358",
            "market inmate woman federal elevator impact brisk essay increase buzz evidence fine",
            dict);
        
        checkMnemonic(entropy2, "", "d26e5a46cc8aaf597cad072a4e2333d19d2c0c395eb8d0a7fb47c36958618bc02cc548958920fcd1962bdb84757f82dfbaf89f41cfbe5c2ccbaba270fe939ce4",
            "spoon sing upset another glass nasty horror such nerve damp equip loop virtual toe deposit prefer half poet time calm believe adjust coral lens",
            dict);
    }
}
