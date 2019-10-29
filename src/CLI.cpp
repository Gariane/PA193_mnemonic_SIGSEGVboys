#include "dictionary.hpp"
#include "mnemonic.hpp"

using BIP39::Dictionary;
using BIP39::Mnemonic;

#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <cstring>

class Parser {
private:
    bool check = false;
    bool generate = false;
    bool reverse = false;
    std::string dictionary;
    std::string entropy;
    std::string phrase;
    std::string seed;
    std::string password;
    option long_options[7] =
            {
                    {"help", no_argument, nullptr, 'h'},
                    {"dictionary", required_argument, nullptr, 'd'},
                    {"password", required_argument, nullptr, 'p'},
                    {"check", required_argument, nullptr, 'c'},
                    {"generate", required_argument, nullptr, 'g'},
                    {"reverse", required_argument, nullptr, 'r'},
                    {nullptr, no_argument, nullptr, 0}
            };

    void checkDict() {
        if(dictionary.empty()) {
            std::cerr << "No dictionary specified";
            exit(1);
        }
    }

    void cleanUp() {
        memset(password.data(), 0, password.length());
        memset(phrase.data(), 0, phrase.length());
        memset(seed.data(), 0, seed.length());
        memset(entropy.data(), 0, entropy.length());
    }

    void funcGenerate() {
        std::ifstream input(entropy);
        if (input.fail()) {
            throw std::invalid_argument("Invalid path: " + entropy);
        }
        std::stringstream buffer;
        buffer << input.rdbuf();
        checkDict();
        Dictionary dict(dictionary);
        Mnemonic mnem(buffer.str(), password, dict, Mnemonic::fromEntropy::Entropy);
        std::cout << "Generating from entropy: " << mnem.getEntropy() << std::endl;
        std::cout << "---------------------------------------------------------------------" << std::endl;
        std::cout << "Generated phrase: " << mnem.getPhrase() << std::endl;
        std::cout << "Generated seed: " << mnem.getSeed() << std::endl;
        cleanUp();
    }

    void funcReverse() {
        std::ifstream input(phrase);
        if (input.fail()) {
            throw std::invalid_argument("Invalid path: " + phrase);
        }
        std::stringstream buffer;
        buffer << input.rdbuf();
        checkDict();
        Dictionary dict(dictionary);
        Mnemonic mnem(buffer.str(), password, dict, Mnemonic::fromPhrase::Phrase);
        std::cout << "Generated from phrase: " << mnem.getPhrase() << std::endl;
        std::cout << "---------------------------------------------------------------------" << std::endl;
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
        std::stringstream buffer, buffer2;
        buffer << input.rdbuf();
        buffer2 << input2.rdbuf();
        checkDict();
        Dictionary dict(dictionary);
        Mnemonic mnem(buffer.str(), password, dict, Mnemonic::fromPhrase::Phrase);
        if(mnem.getSeed() == buffer2.str()) {
            std::cout << "OK - provided phrase generated expected seed" << std::endl;
        } else {
            std::cout << "NOK - provided phrase did NOT generated expected seed" << std::endl;
        }
        cleanUp();
    }

public:
    Parser(int argc, char** argv) {
        char ch;
        while ((ch = getopt_long(argc, argv, "hd:p:c:g:r:", long_options, nullptr)) != -1)
        {
            // check to see if a single character or long option came through
            switch (ch)
            {
                case 'h':
                    printHelp();
                    exit(0);
                case 'd':
                    dictionary = optarg;
                    break;
                case 'p':
                    password = optarg;
                    break;
                case 'c':
                    if(generate || reverse) {
                        std::cerr << "A function has already been specified";
                        exit(1);
                    }
                    check = true;
                    if (optind < argc && argv[optind][0] != '-') {
                        phrase = optarg;
                        seed = argv[optind];
                        optind++;
                    } else {
                        std::cerr << "Wrong parameter specified, use -h or --help for usage info";
                        printHelp();
                        exit(1);
                    }
                    break;
                case 'g':
                    if(check || reverse) {
                        std::cerr << "A function has already been specified";
                        exit(1);
                    }
                    generate = true;
                    entropy = optarg;
                    break;
                case 'r':
                    if(check || generate) {
                        std::cerr << "A function has already been specified";
                        exit(1);
                    }
                    reverse = true;
                    phrase = optarg;
                    break;
                default:
                    std::cerr << "Wrong parameter specified, use -h or --help for usage info";
                    printHelp();
                    exit(1);
            }
        }
        if(generate) funcGenerate();
        if(reverse) funcReverse();
        if(check) funcCheck();
    }

    //TODO remove when not needed
    /*void printArguments() {
        std::cout << "Dictionary: " << dictionary << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << "Entropy: " << entropy << std::endl;
        std::cout << "Phrase: " << phrase << std::endl;
        std::cout << "Seed: " << seed << std::endl;
        if(check) std::cout << "-c ";
        if(generate) std::cout << "-g ";
        if(reverse) std::cout << "-r ";
    }*/

    static void printHelp() {
        std::cout << "Arguments:" << std::endl;
        std::cout << "-h --help                                 Prints help" << std::endl;
        std::cout << "-d --dictionary <path>                    Sets path to file with dictionary" << std::endl;
        std::cout << "-p --password <password>                  Sets password" << std::endl;
        std::cout << "-c --check <phrase> <seed>                Check = phrase & seed -> OK/NOK" << std::endl;
        std::cout << "-g --generate <entropy>                   Generate = entropy -> seed and phrase" << std::endl;
        std::cout << "-r --reverse <phrase>                     Reverse = phrase -> entropy and seed" << std::endl;
    }
};

int main(int argc, char** argv) {
    Parser parser(argc, argv);
}

