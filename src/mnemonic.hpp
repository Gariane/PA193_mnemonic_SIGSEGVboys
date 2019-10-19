#ifndef MNEMONIC_HPP
#define MNEMONIC_HPP

#include <string>
#include <vector>
#include <array>

#define DICTIONARY_SIZE 2048

namespace BIP39 {

class Dictionary {
    const std::array<std::wstring, DICTIONARY_SIZE> keyWords;

   public:
    Dictionary(const std::string& path);

    //maybe throws an exception when index is out of range, whoknows
    const std::string& getWord(unsigned index) const;

    unsigned getIndex(const std::wstring keyword) const;
};

class Mnemonic {
   public:
    // TBD - is this data type OK?
    using binData = std::vector<uint32_t>;

   public:
    // TBD do we take path to file or filedescriptor directly?
    Mnemonic(binData entropy, const std::string& dictionaryPath);
    Mnemonic(const std::vector<std::string>& phrase,
             const std::string& dictionaryPath);

    binData getEntropy() const;
    std::string getPhrase() const;
    std::string getSeed() const;

    static bool checkPhraseSeedPair(const std::vector<std::string>& phrase,
                                    const std::string& seed,
                                    const std::string& dictionaryPath);
};

}  // end namespace BIP39

#endif
