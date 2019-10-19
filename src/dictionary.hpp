#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <functional>
#include <typeinfo>

#define DICTIONARY_SIZE 2048

namespace BIP39 {

class Dictionary {
    std::array<std::wstring, DICTIONARY_SIZE> keyWords;
    bool sorted;

    void parseFile(const std::string& path) {
        std::wifstream input(path);
        std::locale loc("");
        input.imbue(loc);
        if (input.fail()) {
            throw std::invalid_argument("Invalid path: " + path);
        }
        std::wstring current;
        int count = 0;
        while (!input.eof()) {
            std::getline(input, current);
            if (input.eof()) {
                break;
            }
            if (count >= DICTIONARY_SIZE) {
                throw std::length_error(
                    "Dictionary too long (2048 keywords expected)");
            }
            for (wchar_t chr : current) {
                if (std::isspace(chr, loc)) {
                    throw std::invalid_argument("Invalid character on line " +
                                                std::to_string(count));
                }
            }
            keyWords[count] = current;
            count++;
        }
        if (count < DICTIONARY_SIZE) {
            throw std::length_error(
                "Dictionary too short (2048 keywords expected)");
        }
        auto begin = keyWords.begin();
        auto end = keyWords.end();
        if ( !(sorted = std::is_sorted(begin, end)) ) {
            sorted = false;
        }
    }

   public:
    explicit Dictionary(const std::string& path) : keyWords(), sorted(true) { parseFile(path); }

    // maybe throws an exception when index is out of range, whoknows
    const std::wstring& getWord(unsigned index) const {
        return keyWords.at(index);
    }

    unsigned getIndex(const std::wstring& keyword) const {
        if ( sorted ) {
            auto iterator = std::lower_bound(keyWords.begin(), keyWords.end(), keyword);
            if ( iterator == keyWords.end() ) {
                throw std::out_of_range("Keyword not present in dictionary");
            }
            return std::distance(keyWords.begin(), iterator);
        } else {
            auto iterator = std::find(keyWords.begin(), keyWords.end(), keyword);
            if ( iterator == keyWords.end() ) {
                throw std::out_of_range("Keyword not present in dictionary");
            }
            return std::distance(keyWords.begin(), iterator);
        }
    }
};

}  // end namespace BIP39

#endif
