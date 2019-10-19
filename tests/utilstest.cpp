#include "catch.hpp"
#include <string>
#include "dictionary.hpp"


TEST_CASE("DICTIONARY-INVALIDPATH-THROWS") {
    const std::string path("/path/that/hopefully/doesnt/exist");
    REQUIRE_THROWS_AS(BIP39::Dictionary(path), std::invalid_argument);
}
