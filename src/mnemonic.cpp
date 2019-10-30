#include "mnemonic.hpp"

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace {

// following two functions were inspired by
// https://tweex.net/post/c-anything-tofrom-a-hex-string/

std::vector<uint8_t> stringToBytes(const std::string &in) {
    size_t length = in.length();

    std::vector<uint8_t> out;
    out.reserve(length / 2);

    std::stringstream hexStringStream;
    hexStringStream >> std::hex;

    for (size_t strIndex = 0, dataIndex = 0; strIndex < length; ++dataIndex) {
        const char tmpStr[3] = {in[strIndex++], in[strIndex++], 0};

        hexStringStream.clear();
        hexStringStream.str(tmpStr);

        int tmpValue = 0;
        hexStringStream >> tmpValue;
        out.push_back(static_cast<unsigned char>(tmpValue));
    }

    return out;
}

std::string bytesToString(const uint8_t *data, size_t dataLength) {
    std::stringstream hexStringStream;

    hexStringStream << std::hex << std::setfill('0');
    for (size_t index = 0; index < dataLength; ++index) {
        hexStringStream << std::setw(2) << static_cast<int>(data[index]);
    }

    return hexStringStream.str();
}

std::string bytesToString(const std::vector<uint8_t> &data) {
    return bytesToString(data.data(), data.size());
}

}  // end of anonymous namespace

namespace BIP39 {

Mnemonic::Mnemonic(std::string entropy, const std::string &passphrase,
                   const BIP39::Dictionary &dict,
                   BIP39::Mnemonic::fromEntropy /* unused */)
    : originalEntropy_(std::move(entropy)) {
    if (originalEntropy_.length() < 32 || originalEntropy_.length() > 64 ||
        originalEntropy_.length() % 8 != 0) {
        throw std::invalid_argument("Entropy size is invalid");
    }

    std::transform(originalEntropy_.begin(), originalEntropy_.end(),
                   originalEntropy_.begin(),
                   [](char c) { return std::tolower(c); });
    if (originalEntropy_.find_first_not_of("1234567890abcdef") !=
        std::string::npos) {
        throw std::invalid_argument("Entropy is not hexadecimal string");
    }

    std::vector<uint8_t> entropyChar = stringToBytes(originalEntropy_);

    uint8_t checksum = calculateChecksum(entropyChar);
    entropyChar.push_back(checksum);

    uint16_t currIndex = 0;
    int counter = 0;

    for (uint8_t val : entropyChar) {
        for (int i = 0; i < 8; ++i) {
            bool currBitInVal = (val & (0x80 >> i));
            if (currBitInVal) {
                currIndex |= 0x8000 >> (5 + counter);
            }

            if (++counter == 11) {
                try {
                    addToPhrase(dict.getWord(currIndex));
                } catch (const std::out_of_range &e) {
                    throw std::runtime_error(
                        "Mnemonic sentence generation failed");
                }
                counter = 0;
                currIndex = 0;
            }
        }
    }

    seed_ = generateSeed(phrase_, passphrase);
}

Mnemonic::Mnemonic(std::string phrase, const std::string &passphrase,
                   const BIP39::Dictionary &dict,
                   BIP39::Mnemonic::fromPhrase /* unused */)
    : phrase_(std::move(phrase)) {
    std::vector<uint8_t> entropyChar = getBytesFromPhrase(phrase_, dict);
    std::vector<uint8_t> entropyWithoutChecksum = {entropyChar.begin(),
                                                   entropyChar.end() - 1};

    uint8_t checksum = calculateChecksum(entropyWithoutChecksum);

    if (checksum != entropyChar.back()) {
        throw std::invalid_argument(
            "Phrase checksum is not valid with supplied dictionary");
    }

    originalEntropy_ = bytesToString(entropyWithoutChecksum);
    seed_ = generateSeed(phrase_, passphrase);
}

std::string Mnemonic::getEntropy() const { return originalEntropy_; }

std::string Mnemonic::getPhrase() const { return phrase_; }

std::string Mnemonic::getSeed() const { return seed_; }

bool Mnemonic::checkPhraseSeedPair(const std::string &phrase,
                                   const std::string &seed,
                                   const std::string &passphrase,
                                   const BIP39::Dictionary &dict) {
    std::vector<uint8_t> entropyChar = getBytesFromPhrase(phrase, dict);
    uint8_t checksum =
        calculateChecksum({entropyChar.begin(), entropyChar.end() - 1});

    if (checksum != entropyChar.back()) {
        throw std::invalid_argument(
            "Phrase checksum is not valid with supplied dictionary");
    }

    return generateSeed(phrase, passphrase) == seed;
}

std::string Mnemonic::generateSeed(const std::string &mnemonic,
                                   const std::string &passphrase = "") {
    unsigned char out[64];
    std::string salt = "mnemonic" + passphrase;

    int ret =
        PKCS5_PBKDF2_HMAC(mnemonic.c_str(), mnemonic.length(),
                          reinterpret_cast<const unsigned char *>(salt.c_str()),    // NOLINT must use reinterpret_cast
                          salt.length(),
                          2048, EVP_sha512(), 64, out);

    if (ret != 1) {
        throw std::runtime_error("Seed generation failed");
    }

    return bytesToString(out, 64);
}

uint8_t Mnemonic::calculateChecksum(const std::vector<uint8_t> &entropy) {
    int CS = entropy.size() / 4;

    int ret = 0;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    ret = SHA256_Init(&sha256);
    if (ret != 1) {
        throw std::runtime_error("Checksum calculation failed");
    }

    ret = SHA256_Update(&sha256, entropy.data(), entropy.size());
    if (ret != 1) {
        throw std::runtime_error("Checksum calculation failed");
    }

    ret = SHA256_Final(hash, &sha256);
    if (ret != 1) {
        throw std::runtime_error("Checksum calculation failed");
    }

    return (hash[0] & (0xFF << (8 - CS)));
}

std::vector<uint8_t> Mnemonic::getBytesFromPhrase(const std::string &phrase,
                                                  const Dictionary &dict) {
    std::vector<uint8_t> entropyChar;

    int counter = 0;
    uint8_t currentChar = 0;

    std::istringstream parser(phrase);
    std::string str;
    while (parser >> str) {
        uint16_t val = 0;
        try {
            val = dict.getIndex(str);
        } catch (const std::out_of_range &e) {
            throw std::invalid_argument(
                "Phrase contains word not present in dictionary: " + str);
        }

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

void Mnemonic::addToPhrase(const std::string &word) {
    if (!phrase_.empty()) {
        phrase_ += " ";
    }

    phrase_ += word;
}

}  // end namespace BIP39
