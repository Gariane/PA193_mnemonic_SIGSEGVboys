#include "mnemonic.hpp"

namespace BIP39 {    

Mnemonic::Mnemonic(binData entropy, const BIP39::Dictionary& dictionaryPath) {

}

Mnemonic::Mnemonic(const std::vector<std::string>& phrase, const BIP39::Dictionary& dictionaryPath) {

}

Mnemonic::binData Mnemonic::getEntropy() const {

}

std::string Mnemonic::getPhrase() const {

}

std::string Mnemonic::getSeed() const {

}

bool Mnemonic::checkPhraseSeedPair(const std::vector<std::string>& phrase, const std::string& seed, const BIP39::Dictionary& dictionaryPath) {

}

} // end namespace BIP39