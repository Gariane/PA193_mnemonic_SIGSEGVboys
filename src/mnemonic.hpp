#ifndef MNEMONIC_HPP
#define MNEMONIC_HPP

#include <string>
#include <vector>
#include <array>

#include "dictionary.hpp"

#define DICTIONARY_SIZE 2048

namespace BIP39 {

class Mnemonic {
   public:
    // TBD - is this data type OK?
    using binData = std::vector<uint32_t>;

   public:
    // TBD do we take path to file or filedescriptor directly?
    Mnemonic(binData entropy, const BIP39::Dictionary& dictionaryPath);
    Mnemonic(const std::wstring& phrase,
             const BIP39::Dictionary& dictionaryPath);

    binData getEntropy() const;
    std::wstring getPhrase() const;
    std::string getSeed() const;

    static bool checkPhraseSeedPair(const std::wstring& phrase,
                                    const std::string& seed,
                                    const BIP39::Dictionary& dictionaryPath);
   private:
    binData originalEntropy;
    std::wstring phrase;
    std::string seed;
};

}  // end namespace BIP39

#endif
