#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <array>
#include <fstream>
#include <locale>
#include <string>

#define DICTIONARY_SIZE 2048

namespace BIP39 {

class Dictionary {
    std::array<std::wstring, DICTIONARY_SIZE> keyWords;
    bool sorted;


    bool check_uniqueness(int size, const std::wstring& item) {
        auto start = keyWords.begin();
        auto end = keyWords.begin() + size;
        auto search = std::find(start, end, item);
        return search == end;
    }


    bool checkWhiteSpaces(const std::wstring& checked, const std::locale& loc) {
        for (wchar_t chr : checked) {
            if (std::isspace(chr, loc)) {
                return false;
            }
        }
        return true;
    }

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
            if (input.eof() || input.bad()) {
                break;
            }
            if (count >= DICTIONARY_SIZE) {
                throw std::length_error(
                    "Dictionary too long (2048 keywords expected)");
            }
            if ( !checkWhiteSpaces(current, loc) ) {
                throw std::invalid_argument("Invalid character on line " +
                                                std::to_string(count + 1));
            }
            if ( !check_uniqueness(count , current) ) {
                throw std::invalid_argument("Duplicate word on line " + std::to_string(count + 1));
            }
            keyWords[count] = current;
            count++;
        }
        if (count < DICTIONARY_SIZE) {
            throw std::length_error(
                "Dictionary too short (2048 keywords expected)");
        }
        if ( !(sorted = std::is_sorted(keyWords.begin(), keyWords.end())) ) {
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
        auto iterator = keyWords.begin();
        if ( sorted ) {
            iterator = std::lower_bound(keyWords.begin(), keyWords.end(), keyword);
        } else {
            iterator = std::find(keyWords.begin(), keyWords.end(), keyword);
        }
        if ( iterator == keyWords.end() ) {
            throw std::out_of_range("Keyword not present in dictionary");
        }
        return std::distance(keyWords.begin(), iterator);
    }
};

}  // end namespace BIP39

#endif
