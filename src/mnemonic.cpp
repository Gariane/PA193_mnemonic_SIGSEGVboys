#include <openssl/sha.h>
#include <iostream>
#include <bitset>
#include "mnemonic.hpp"

namespace BIP39 {    

Mnemonic::Mnemonic(binData entropy, const BIP39::Dictionary& dictionaryPath):originalEntropy(entropy) {
    assert(entropy.size() >= 4 && entropy.size() <= 8);
    int CS = entropy.size();

    std::vector<unsigned char> entropyChar;
    entropyChar.reserve(entropy.size() * 4);
    for (size_t i = 0; i < entropy.size(); ++i) {
        uint32_t num = entropy[i];
        for (size_t j = 0; j < 4; ++j ) {
            unsigned char c = reinterpret_cast<unsigned char*>(&num)[3-j];
            entropyChar[i * 4 + j] = c;
        }
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, entropyChar.data(), entropy.size() * 4);
    SHA256_Final(hash, &sha256);

    uint32_t checksum = (hash[0] & (0xFF << (8 - CS)));
    int words = (entropy.size() * 32 + CS) / 11;

    entropy.push_back(checksum << (32 - CS - (8 - CS)));  

    int wordCounter = 0;
    uint32_t currIndex = 0;
    int counter = 0;

    std::wstring separator = L"";
    for (uint32_t val : entropy) {

       for (int i = 0; i < 32; ++i) {
          bool currBitInVal = (val & (0x80000000 >> i));
          if (currBitInVal) {
              currIndex |= 0x80000000 >> ( 21 + counter ); 
          }

          if (++counter == 11) {
              std::wstring x = dictionaryPath.getWord(currIndex);
              phrase += separator + x;
              separator = L" ";
              counter = 0;
              currIndex = 0;
              if (++wordCounter == words) {
                  break;
              }
          }
       } 

    }


}

Mnemonic::Mnemonic(const std::wstring& phrase, const BIP39::Dictionary& dictionaryPath) {

}

Mnemonic::binData Mnemonic::getEntropy() const {
    return originalEntropy;
}

std::wstring Mnemonic::getPhrase() const {
    return phrase;
}

std::string Mnemonic::getSeed() const {
    return seed;
}

bool Mnemonic::checkPhraseSeedPair(const std::wstring& phrase, const std::string& seed, const BIP39::Dictionary& dictionaryPath) {
    return true;
}

} // end namespace BIP39
