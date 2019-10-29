#ifndef MNEMONIC_HPP
#define MNEMONIC_HPP

#include <string>
#include <vector>

#include "dictionary.hpp"

namespace BIP39 {

class Mnemonic {
   public:
     enum class fromEntropy { Entropy };
     enum class fromPhrase { Phrase };

   public:
    Mnemonic(std::string entropy, const std::string& passphrase, const BIP39::Dictionary& dict, fromEntropy = fromEntropy::Entropy);
    Mnemonic(std::string phrase, const std::string& passphrase, const BIP39::Dictionary& dict, fromPhrase);

    std::string getEntropy() const;
    std::string getPhrase() const;
    std::string getSeed() const;

    static bool checkPhraseSeedPair(const std::string& phrase,
                                    const std::string& seed,
                                    const std::string& passphrase,
                                    const BIP39::Dictionary& dict);
   private:
    std::string originalEntropy_;
    std::string phrase_;
    std::string seed_;

    /* Maybe move these static to local functions in .cpp file */
    static std::string generateSeed(const std::string& mnemonic, const std::string& passphrase);
    static uint8_t calculateChecksum(const std::vector<uint8_t>& entropy); 
    static std::vector<uint8_t> getBytesFromPhrase(const std::string& phrase, const Dictionary& dict);

    void addToPhrase(const std::string& word);
};

}  // end namespace BIP39

#endif
