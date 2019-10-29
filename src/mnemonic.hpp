#ifndef MNEMONIC_HPP
#define MNEMONIC_HPP

#include <string>
#include <vector>

#include "dictionary.hpp"

namespace BIP39 {

class Mnemonic {
   public:
    Mnemonic(std::string entropy, const std::wstring& passphrase, const BIP39::Dictionary& dict);
    Mnemonic(std::wstring phrase, const std::wstring& passphrase, const BIP39::Dictionary& dict);

    std::string getEntropy() const;
    std::wstring getPhrase() const;
    std::string getSeed() const;

    static bool checkPhraseSeedPair(const std::wstring& phrase,
                                    const std::string& seed,
                                    const std::wstring& passphrase,
                                    const BIP39::Dictionary& dict);
   private:
    std::string originalEntropy_;
    std::wstring phrase_;
    std::string seed_;

    /* Maybe move these static to local functions in .cpp file */
    static std::string generateSeed(const std::wstring& mnemonic, const std::wstring& passphrase);
    static uint8_t calculateChecksum(const std::vector<uint8_t>& entropy); 
    static std::vector<uint8_t> getBytesFromPhrase(const std::wstring& phrase, const Dictionary& dict);

    void addToPhrase(const std::wstring& word);
};

}  // end namespace BIP39

#endif
