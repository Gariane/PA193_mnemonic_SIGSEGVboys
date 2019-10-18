#ifndef MNEMONIC_HPP
#define MNEMONIC_HPP

#include <vector>
#include <string>

namespace libmnemonic {
    
class Mnemonic {
  public:
    // TBD - is this data type OK?
    using binData = std::vector<unsigned char>;

  public:
    // TBD do we take path to file or filedescriptor directly?
    Mnemonic(binData entropy, const std::string& dictionaryPath);
    Mnemonic(const std::vector<std::string>& phrase, const std::string& dictionaryPath);

    binData getPhrase() const;
    binData getSeed() const;
    binData getEntropy() const;
    
    static bool checkPhraseSeedPair(const std::vector<std::string>& phrase, const binData& seed, const std::string& dictionaryPath);
};


} // end namespace libmnemonic

#endif
