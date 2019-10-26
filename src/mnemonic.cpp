#include <sstream>
#include <codecvt>
#include <vector>

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

    for(size_t strIndex = 0, dataIndex = 0; strIndex < length; ++dataIndex)
    {
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
    int CS = entropyChar.size() / 4;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, entropyChar.data(), entropyChar.size());
    SHA256_Final(hash, &sha256);

    uint8_t checksum = (hash[0] & (0xFF << (8 - CS)));
    entropyChar.push_back(checksum);


    int words = (entropyChar.size() * 8 + CS) / 11;

    int wordCounter = 0;
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

              if (++wordCounter == words) {
                  break;
              }
          }
       } 

    }

    seed_ = generateSeed(phrase_);
}

Mnemonic::Mnemonic(const std::wstring& phrase, const BIP39::Dictionary& dict) {

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
    // TODO verify checksum of phrase (last few bits appended from hash)
    // and print warning if doesnt check out
    
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

void Mnemonic::addToPhrase(const std::wstring& word) {
    if (!phrase_.empty()) {
        phrase_ += L" ";
    }

    phrase_ += word;
}

} // end namespace BIP39
