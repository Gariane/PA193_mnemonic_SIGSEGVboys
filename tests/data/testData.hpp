#ifndef testData_hpp
#define testData_hpp

#include <vector>
#include <string>

struct testData {
    std::vector<uint32_t> entropy;
    std::vector<std::string> phrase;
    std::string seed;

    testData(std::vector<uint32_t> entropy, std::vector<std::string> phrase, std::string seed)
      : entropy(std::move(entropy)), phrase(std::move(phrase)), seed(std::move(seed)) {};
};

#endif
