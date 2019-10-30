#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <array>
#include <fstream>
#include <string>

#define DICTIONARY_SIZE 2048

namespace BIP39 {

class Dictionary {
   public:
    explicit Dictionary(const std::string& path);
    explicit Dictionary(std::ifstream& input);

    // maybe throws an exception when index is out of range, whoknows
    std::string getWord(unsigned index) const;

    unsigned getIndex(const std::string& keyword) const;

   private:
    std::array<std::string, DICTIONARY_SIZE> keyWords;
    bool sorted;

    bool checkUniqueness(int size, const std::string& item) const;
    bool checkWhiteSpaces(const std::string& checked) const;
    void parseFile(std::ifstream& input);
};

}  // end namespace BIP39

#endif
