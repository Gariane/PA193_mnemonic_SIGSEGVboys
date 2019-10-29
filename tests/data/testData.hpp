#ifndef testData_hpp
#define testData_hpp

#include <string>

struct testData {
    std::string entropy;
    std::string phrase;
    std::string seed;
    std::string passphrase;

    testData(std::string entropy, std::string phrase, std::string seed, std::string passphrase)
      : entropy(std::move(entropy)), phrase(std::move(phrase)), seed(std::move(seed)), passphrase(std::move(passphrase)) {};
};

#endif
