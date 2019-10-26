#ifndef testData_hpp
#define testData_hpp

#include <string>

struct testData {
    std::string entropy;
    std::wstring phrase;
    std::string seed;

    testData(std::string entropy, std::wstring phrase, std::string seed)
      : entropy(std::move(entropy)), phrase(std::move(phrase)), seed(std::move(seed)) {};
};

#endif
