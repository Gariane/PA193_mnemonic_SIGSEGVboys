/**
 * @file dictionary.hpp
 * @author Radoslav Sabol
 * @brief Dictionary implementation for PA193 group project
 */
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <array>
#include <fstream>
#include <string>

#define DICTIONARY_SIZE 2048

namespace BIP39 {

/**
 * @brief Class represents dictionary for BIP39,
 *  and along parsing provides some basic operations over it
 */
class Dictionary {
   public:
    /**
     * @brief Constructor which loads dictionary into memory while
     * checking its validity, in our implementation the dictionary must
     * meet these conditions:
     * 1. words are separated with newlines, 1 word - 1 line
     *  - that means there should be exactly 2048 lines (std::length_error)
     * 2. No duplicate words are allowed
     *  - it ruins the determinism in mnemonic->entropy transition
     * 3. File has utf-8 encoding
     *  - from the specification of BIP-39
     * 4. Trailing whitespaces, trailing newlines, empty lines,
     *  multiple words on a single line, invalid utf-8 garbage, assignment-4
     * payloads, proofs that Bush did 9/11 are not allowed
     * @param path - path to the UTF-8 encoded dictionary
     * @throws std::length_error on violation of rule 1
     * @throws std::invalid_argument on violation of everything else
     */
    explicit Dictionary(const std::string& path);

    /**
     * @brief Same rules apply for this constructor, the only difference
     * is using open ifstream instead of path
     * @param open ifstream
     */
    explicit Dictionary(std::ifstream& input);

    /**
     * @brief gets word at index i
     * @param index in range 0-2047
     * @return word at index i
     * @throws std::out of range if index is not in allowed range
     */
    std::string getWord(unsigned index) const;

    /**
     * @brief Reverse operation for getWord, gets index of word.
     * This is where the "sorted" flag comes into play - the BIP39 specification
     * suggests that dictionaries SHOULD be sorted for faster binary search,
     * which is not always the case. That's why the parser checks if file is
     * sorted, and if it is - it uses binary search, otherwise it will use
     * sequential search
     * @param keyword: searched word
     * @return index in range 0-2047
     * @throws std::out_of_range if word is not present in the dictionary
     */
    unsigned getIndex(const std::string& keyword) const;

   private:
    std::array<std::string, DICTIONARY_SIZE>
        keyWords;  //< array of size 2048 for storing the dictionary words
    bool sorted;   //< flag indicating if dictionary is sorted, more on that in
                   // getIndex

    bool checkUniqueness(int size, const std::string& item) const;
    bool checkWhiteSpaces(const std::string& checked) const;
    void parseFile(std::ifstream& input);
};

}  // end namespace BIP39

#endif
