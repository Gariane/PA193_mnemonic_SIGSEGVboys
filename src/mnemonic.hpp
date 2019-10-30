/**
 * @file mnemonic.hpp
 * @author Adam Povazanec
 * @brief BIP39 mnemonic phrase and seed generator and verifier for PA193 group project
 */
#ifndef MNEMONIC_HPP
#define MNEMONIC_HPP

#include <string>
#include <vector>

#include "dictionary.hpp"

namespace BIP39 {

/**
 * @brief Class provides functionality to calculate BIP39 mnemonic phrase and seed
 */
class Mnemonic {
   public:
     /**
     * Enum which indicates to constructor that we generate from entropy
     */
    enum class fromEntropy { Entropy };

     /**
     * Enum which indicates to constructor that we generate from mnemonic phrase
     */
    enum class fromPhrase { Phrase };

   public:
    /**
     * @brief Generates mnemonic sentence and seed from supplied entropy, passphrase and dictionary
     * NOTE: last parameter must be BIP39::Mnemonic::fromEntropy::Entropy or left empty, so constructor call is not ambiguous
     * @param entropy hexadecimal string to use as initial entropy, must be 32-64 bytes long and number of bytes must be multiple of 8
     * @param passphrase passphrase to use, no constraints
     * @param dict valid BIP39::Dictionary object used to generate mnemonic sentence
     * @throws std::invalid_argument if initial entropy is not valid
     * @throws std::runtime_error if checksum, seed or mnemonic sentence generation failed
     */
    Mnemonic(std::string entropy, const std::string& passphrase, const BIP39::Dictionary& dict, fromEntropy /* unused */ = fromEntropy::Entropy);

    /**
     * @brief Generates initial entropy and seed from mnemonic phrase and passphrase and dictionary
     * NOTE: last parameter must be BIP39::Mnemonic::fromPhrase::Phrase, so constructor call is not ambiguous
     * @param phrase mnemonic phrase
     * @param passphrase passphrase to be used to generate seed
     * @param dict dictionary, which was used to generate mnemonic sentence
     * @throws std::invalid_argument if phrase contains word not present in dict, or if phrase checksum is not valid
     * @throws std::runtime_error if checksum or seed generation failed
     */
    Mnemonic(std::string phrase, const std::string& passphrase, const BIP39::Dictionary& dict, fromPhrase /* unused */);

    /**
     * @brief Entropy getter
     * @return returns initial entropy as hex string in lowercase
     */
    [[nodiscard]] std::string getEntropy() const;

    /**
     * @brief Phrase getter
     * @return returns mnemonic sentence as string
     */
    [[nodiscard]] std::string getPhrase() const;

    /**
     * @brief Seed getter
     * @return returns seed as hex string in lowercase
     */
    [[nodiscard]] std::string getSeed() const;

    /**
     * @brief Checks if phrase and seed correspond to each other
     * @param phrase valid mnemonic phrase
     * @param seed valid seed
     * @param passphrase passphrase used to generate seed
     * @param dict dictionary used to generate mnemonic phrase
     * @return true if phrase and seed correspond to each other, false otherwise
     * @throws std::invalid_argument if phrase contains word not present in dict, or if phrase checksum is not valid
     * @throws std::runtime_error if checksum or seed generation failed
     */
    static bool checkPhraseSeedPair(const std::string& phrase,
                                    const std::string& seed,
                                    const std::string& passphrase,
                                    const BIP39::Dictionary& dict);
   private:
    std::string originalEntropy_;
    std::string phrase_;
    std::string seed_;

    static std::string generateSeed(const std::string& mnemonic, const std::string& passphrase);
    static uint8_t calculateChecksum(const std::vector<uint8_t>& entropy); 
    static std::vector<uint8_t> getBytesFromPhrase(const std::string& phrase, const Dictionary& dict);

    void addToPhrase(const std::string& word);
};

}  // end namespace BIP39

#endif
