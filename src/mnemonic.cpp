#include <sstream>
#include <iomanip>
#include <codecvt>
#include <cmath>

#include <openssl/sha.h>
#include <openssl/evp.h>

#include "mnemonic.hpp"

namespace {

std::vector<uint8_t> stringToBytes(const std::string& in) {
    size_t length = in.length();

    std::vector<uint8_t> out;
    out.reserve(length / 2);

    std::stringstream hexStringStream; 
    hexStringStream >> std::hex;

    for(size_t strIndex = 0, dataIndex = 0; strIndex < length; ++dataIndex) {
        const char tmpStr[3] = { in[strIndex++], in[strIndex++], 0 };

        hexStringStream.clear();
        hexStringStream.str(tmpStr);

        int tmpValue = 0;
        hexStringStream >> tmpValue;
        out.push_back(static_cast<unsigned char>(tmpValue));
    }

    return out;
}

std::string bytesToString(uint8_t* data, size_t dataLength)
{
    std::stringstream hexStringStream;
    
    hexStringStream << std::hex << std::setfill('0');
    for(size_t index = 0; index < dataLength; ++index) {
        hexStringStream << std::setw(2) << static_cast<int>(data[index]);
    }

    return hexStringStream.str();
}

} // end of anonymous namespace




namespace BIP39 {    

Mnemonic::Mnemonic(std::string entropy, const BIP39::Dictionary& dict):originalEntropy_(std::move(entropy)) {
    std::vector<uint8_t> entropyChar = stringToBytes(originalEntropy_);

    uint8_t checksum = calculateChecksum(entropyChar);
    entropyChar.push_back(checksum);

    uint16_t currIndex = 0;
    int counter = 0;

    for (uint8_t val : entropyChar) {
       for (int i = 0; i < 8; ++i) {
          bool currBitInVal = (val & (0x80 >> i));
          if (currBitInVal) {
              currIndex |= 0x8000 >> ( 5 + counter ); 
          } 

          if (++counter == 11) {
              // TODO bounds checking of index
              addToPhrase(dict.getWord(currIndex));
              counter = 0;
              currIndex = 0;
          }
       } 

    }

    seed_ = generateSeed(phrase_);
}

Mnemonic::Mnemonic(std::wstring phrase, const BIP39::Dictionary& dict):phrase_(std::move(phrase)) {
    std::vector<uint8_t> entropyChar = getBytesFromPhrase(phrase_, dict);

    uint8_t checksum = calculateChecksum({entropyChar.begin(), entropyChar.end() - 1});  

    // TODO error check not assert
    assert(checksum == entropyChar.back());

    originalEntropy_ = bytesToString(entropyChar.data(), entropyChar.size() - 1);
    seed_ = generateSeed(phrase_);
}

std::string Mnemonic::getEntropy() const {
    return originalEntropy_;
}

std::wstring Mnemonic::getPhrase() const {
    return phrase_;
}

std::string Mnemonic::getSeed() const {
    return seed_;
}

bool Mnemonic::checkPhraseSeedPair(const std::wstring& phrase, const std::string& seed, const BIP39::Dictionary& dict) {
    std::vector<uint8_t> entropyChar = getBytesFromPhrase(phrase, dict);
    uint8_t checksum = calculateChecksum({entropyChar.begin(), entropyChar.end() - 1});  

    // TODO error check not assert
    assert(checksum == entropyChar.back());
    
    return generateSeed(phrase) == seed;
}


// THIS method doesn't work properly yet
std::string Mnemonic::generateSeed(const std::wstring& mnemonic) {
    unsigned char out[64];
    std::wstring salt = L"mnemonic" + mnemonic;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    std::string utf8_phrase = myconv.to_bytes(mnemonic);
    std::string utf8_salt = myconv.to_bytes(salt);

    PKCS5_PBKDF2_HMAC(utf8_phrase.c_str(), utf8_phrase.length(),
                       reinterpret_cast<const unsigned char*>(utf8_salt.c_str()),utf8_salt.length(), 2048,
                       EVP_sha512(),
                       64, out);

    return bytesToString(out, 64);
}

uint8_t Mnemonic::calculateChecksum(const std::vector<uint8_t>& entropy) {
    int CS = entropy.size() / 4;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, entropy.data(), entropy.size());
    SHA256_Final(hash, &sha256);

    return (hash[0] & (0xFF << (8 - CS)));
}

std::vector<uint8_t> Mnemonic::getBytesFromPhrase(const std::wstring& phrase, const Dictionary& dict) {
    std::vector<uint8_t> entropyChar;

    int counter = 0;
    uint8_t currentChar = 0;

    std::wistringstream parser(phrase);
    std::wstring str;
    while (parser >> str) {
        // TODO error checking
        uint16_t val = dict.getIndex(str);
        for (int i = 0; i < 11; ++i) {
            bool currentBitInVal = (val & (0x8000 >> (5 + i)));
            if (currentBitInVal) {
                currentChar |= 0x80 >> counter;
            }
            
            if (++counter == 8) {
                entropyChar.push_back(currentChar);
                counter = 0;
                currentChar = 0;
            }
        }
    }
    if (counter != 0) {
        entropyChar.push_back(currentChar);
    }

    return entropyChar;
}

void Mnemonic::addToPhrase(const std::wstring& word) {
    if (!phrase_.empty()) {
        phrase_ += L" ";
    }

    phrase_ += word;
}

} // end namespace BIP39
