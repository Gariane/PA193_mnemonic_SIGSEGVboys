#ifndef testData_hpp
#define testData_hpp

#include <string>

struct testData {
    std::string entropy;
    std::wstring phrase;
    std::string seed;
    std::wstring passphrase;

    testData(std::string entropy, std::wstring phrase, std::string seed, std::wstring passphrase)
      : entropy(std::move(entropy)), phrase(std::move(phrase)), seed(std::move(seed)), passphrase(std::move(passphrase)) {};
};

#endif
