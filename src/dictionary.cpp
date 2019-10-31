#include "dictionary.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

#define DICTIONARY_SIZE 2048

namespace BIP39 {

bool Dictionary::checkUniqueness(int size, const std::string &item) const {
    auto start = keyWords.begin();
    auto end = keyWords.begin() + size;
    auto search = std::find(start, end, item);
    return search == end;
}

bool Dictionary::checkWhiteSpaces(const std::string &checked) const {
    if (checked.empty()) {
        return false;
    }

    for (char chr : checked) {
        if (std::isspace(chr)) {
            return false;
        }
    }

    return true;
}

void Dictionary::parseFile(std::ifstream &input) {
    std::string current;
    char buf[1025];
    int count = 0;
    while (!input.eof()) {
        //std::getline(input, current);
        input.getline(buf, 1025);
        current = buf;
        if (input.bad()) {
            throw std::invalid_argument("Stream error");
        }
        if ( current.length() != 1024 && input.eof()) {
            break;
        }
        if (input.fail()) {
            throw std::length_error(
                "Maximum keyword length exceeded (1024)");
        }
        if (count >= DICTIONARY_SIZE) {
            throw std::length_error(
                "Dictionary too long (2048 keywords expected)");
        }
        if (!current.empty() && current.back() == '\r') {
            current.pop_back();
        }
        if (!checkWhiteSpaces(current)) {
            throw std::invalid_argument("Line no. " +
                                        std::to_string(count + 1));
        }
        if (!checkUniqueness(count, current)) {
            throw std::invalid_argument("Duplicate word on line " +
                                        std::to_string(count + 1));
        }
        keyWords[count] = current;
        count++;
    }
    if (count < DICTIONARY_SIZE) {
        throw std::length_error(
            "Dictionary too short (2048 keywords expected)");
    }
    sorted = std::is_sorted(keyWords.begin(), keyWords.end());
}

Dictionary::Dictionary(const std::string &path) : sorted(true) {
    std::ifstream input(path);
    if (input.fail() || !input.is_open()) {
        throw std::invalid_argument("Invalid path: " + path);
    }
    parseFile(input);
}

Dictionary::Dictionary(std::ifstream &input) : sorted(true) {
    parseFile(input);
}

// maybe throws an exception when index is out of range, whoknows
std::string Dictionary::getWord(unsigned index) const {
    return keyWords.at(index);
}

unsigned Dictionary::getIndex(const std::string &keyword) const {
    auto iterator =         // NOLINT just here to be able to use 'auto'
        keyWords.begin();
    if (sorted) {
        iterator = std::lower_bound(keyWords.begin(), keyWords.end(), keyword);
    } else {
        iterator = std::find(keyWords.begin(), keyWords.end(), keyword);
    }
    if (iterator == keyWords.end() || keyword != *iterator) {
        throw std::out_of_range("Keyword not present in dictionary");
    }
    return std::distance(keyWords.begin(), iterator);
}

}  // end of namespace BIP39
