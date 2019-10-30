#include "dictionary.hpp"
#include "mnemonic.hpp"

using BIP39::Dictionary;
using BIP39::Mnemonic;

#include <getopt.h>

#include <algorithm>
#include <iostream>
#include <sstream>

class Parser {
   private:
    bool check = false;
    bool generate = false;
    bool reverse = false;
    bool taskSpecified = false;
    std::string dictionary;
    std::string entropy;
    std::string phrase;
    std::string seed;
    std::string password;
    option long_options[7] = {{"help", no_argument, nullptr, 'h'},
                              {"dictionary", required_argument, nullptr, 'd'},
                              {"password", required_argument, nullptr, 'p'},
                              {"check", required_argument, nullptr, 'c'},
                              {"generate", required_argument, nullptr, 'g'},
                              {"reverse", required_argument, nullptr, 'r'},
                              {nullptr, no_argument, nullptr, 0}};

    void checkDictPath() {
        if (dictionary.empty()) {
            std::cerr << "No dictionary specified" << std::endl;
            std::exit(1);
        }
    }

    Dictionary checkDictThrow() {
        try {
            return Dictionary(dictionary);
        } catch (std::length_error &error) {
            std::cerr << error.what() << std::endl;
            std::exit(1);
        } catch (std::invalid_argument &error) {
            std::cerr << error.what() << std::endl;
            std::exit(1);
        }
    }

    Mnemonic checkMnemThrow(const std::stringstream &buffer,
                            const Dictionary &dict, bool fromEntropy) {
        try {
            if (fromEntropy) {
                return Mnemonic(buffer.str(), password, dict,
                                Mnemonic::fromEntropy::Entropy);
            }
            return Mnemonic(buffer.str(), password, dict,
                                Mnemonic::fromPhrase::Phrase);
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
            std::exit(1);
        } catch (std::invalid_argument &error) {
            std::cerr << error.what() << std::endl;
            std::exit(1);
        }
    }

    bool checkPhraseThrow(const std::stringstream &phraseBuffer,
                          const std::stringstream &seedBuffer,
                          const Dictionary &dict) {
        try {
            return Mnemonic::checkPhraseSeedPair(
                phraseBuffer.str(), seedBuffer.str(), password, dict);
        } catch (std::invalid_argument &error) {
            std::cerr << error.what() << std::endl;
            std::exit(1);
        }
    }

    void cleanUp() {
        std::fill(password.begin(), password.end(), 0);
        std::fill(phrase.begin(), phrase.end(), 0);
        std::fill(seed.begin(), seed.end(), 0);
        std::fill(entropy.begin(), entropy.end(), 0);
    }

    void funcGenerate() {
        std::ifstream input(entropy);
        if (input.fail()) {
            throw std::invalid_argument("Invalid path: " + entropy);
        }
        std::stringstream entropyBuffer;
        entropyBuffer << input.rdbuf();
        checkDictPath();
        Dictionary dict = checkDictThrow();
        Mnemonic mnem = checkMnemThrow(entropyBuffer, dict, true);
        std::cout << "Generating from entropy: " << mnem.getEntropy()
                  << std::endl;
        std::cout
            << "-------------------------------------------------------------"
               "--------"
            << std::endl;
        std::cout << "Generated phrase: " << mnem.getPhrase() << std::endl;
        std::cout << "Generated seed: " << mnem.getSeed() << std::endl;
        cleanUp();
    }

    void funcReverse() {
        std::ifstream input(phrase);
        if (input.fail()) {
            throw std::invalid_argument("Invalid path: " + phrase);
        }
        std::stringstream phraseBuffer;
        phraseBuffer << input.rdbuf();
        checkDictPath();
        Dictionary dict = checkDictThrow();
        ;
        Mnemonic mnem = checkMnemThrow(phraseBuffer, dict, false);
        std::cout << "Generated from phrase: " << mnem.getPhrase() << std::endl;
        std::cout
            << "-------------------------------------------------------------"
               "--------"
            << std::endl;
        std::cout << "Generated entropy: " << mnem.getEntropy() << std::endl;
        std::cout << "Generated seed: " << mnem.getSeed() << std::endl;
        cleanUp();
    }

    void funcCheck() {
        std::ifstream input(phrase);
        if (input.fail()) {
            throw std::invalid_argument("Invalid path: " + phrase);
        }
        std::ifstream input2(seed);
        if (input2.fail()) {
            throw std::invalid_argument("Invalid path: " + seed);
        }
        std::stringstream phraseBuffer, seedBuffer;
        phraseBuffer << input.rdbuf();
        seedBuffer << input2.rdbuf();
        checkDictPath();
        Dictionary dict = checkDictThrow();
        ;
        bool ok = checkPhraseThrow(phraseBuffer, seedBuffer, dict);
        if (ok) {
            std::cout << "OK - provided phrase generated expected seed"
                      << std::endl;
        } else {
            std::cout << "NOK - provided phrase did NOT generated expected seed"
                      << std::endl;
        }
        cleanUp();
    }

   public:
    Parser(int argc, char **argv) {
        char ch;
        while ((ch = getopt_long(argc, argv, "hd:p:c:g:r:", long_options,
                                 nullptr)) != -1) {
            // check to see if a single character or long option came through
            switch (ch) {
                case 'h':
                    printHelp();
                    std::exit(0);
                case 'd':
                    dictionary = optarg;
                    break;
                case 'p':
                    password = optarg;
                    break;
                case 'c':
                    if (taskSpecified) {
                        std::cerr << "A function has already been specified, please choose only 1" << std::endl;
                        std::exit(1);
                    }
                    check = true;
                    taskSpecified = true;
                    if (optind < argc && argv[optind][0] != '-') {
                        phrase = optarg;
                        seed = argv[optind];
                        optind++;
                    } else {
                        std::cerr << "Wrong parameter specified" << std::endl;
                        printHelp();
                        std::exit(1);
                    }
                    break;
                case 'g':
                    if (taskSpecified) {
                        std::cerr << "A function has already been specified, please choose only 1" << std::endl;
                        std::exit(1);
                    }
                    generate = true;
                    taskSpecified = true;
                    entropy = optarg;
                    break;
                case 'r':
                    if (taskSpecified) {
                        std::cerr << "A function has already been specified, please choose only 1" << std::endl;
                        std::exit(1);
                    }
                    reverse = true;
                    taskSpecified = true;
                    phrase = optarg;
                    break;
                default:
                    std::cerr << "Wrong parameter specified" << std::endl;
                    printHelp();
                    std::exit(1);
            }
        }
        if(!taskSpecified) {
            std::cerr << "No task specified to perform, use one of -c -g -r flags" << std::endl;
            printHelp();
            std::exit(1);
        }
        if (generate) funcGenerate();
        if (reverse) funcReverse();
        if (check) funcCheck();
    }

    static void printHelp() {
        std::cout << "Arguments:" << std::endl;
        std::cout << "-h --help                                 Prints help"
                  << std::endl;
        std::cout
            << "-d --dictionary <path>                    Sets path to file "
               "with dictionary"
            << std::endl;
        std::cout << "-p --password <password>                  Sets password"
                  << std::endl;
        std::cout
            << "-c --check <phrase> <seed>                Check = phrase & "
               "seed -> OK/NOK"
            << std::endl;
        std::cout
            << "-g --generate <entropy>                   Generate = entropy "
               "-> seed and phrase"
            << std::endl;
        std::cout
            << "-r --reverse <phrase>                     Reverse = phrase "
               "-> entropy and seed"
            << std::endl;
    }
};

int main(int argc, char **argv) { Parser parser(argc, argv); }
