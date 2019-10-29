#include "dictionary.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>

class Parser {
private:
    bool check = false;
    bool generate = false;
    bool reverse = false;
    std::string dictionary = "";
    std::string entropy = "";
    std::string mnemonic = "";
    std::string password = "";
    option long_options[9] =
            {
                    {"help", no_argument, nullptr, 'h'},
                    {"dictionary", required_argument, nullptr, 'd'},
                    {"entropy", required_argument, nullptr, 'e'},
                    {"mnemonic", required_argument, nullptr, 'm'},
                    {"password", required_argument, nullptr, 'p'},
                    {"check", no_argument, nullptr, 'c'},
                    {"generate", no_argument, nullptr, 'g'},
                    {"reverse", no_argument, nullptr, 'r'},
                    {nullptr, no_argument, nullptr, 0}
            };
public:
    Parser(int argc, char** argv) {
        char ch;
        while ((ch = getopt_long(argc, argv, "hd:e:m:p:cgr", long_options, nullptr)) != -1)
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
                case 'e':
                    entropy = optarg;
                    break;
                case 'm':
                    mnemonic = optarg;
                    break;
                case 'p':
                    password = optarg;
                    break;
                case 'c':
                    check = true;
                    break;
                case 'g':
                    generate = true;
                    break;
                case 'r':
                    reverse = true;
                    break;
                default:
                    printHelp();
                    break;
            }
        }
    }

    void printArguments() {
        std::cout << "-d " << dictionary << std::endl;
        std::cout << "-e " << entropy << std::endl;
        std::cout << "-m " << mnemonic << std::endl;
        std::cout << "-p " << password << std::endl;
        if(check) std::cout << "-c ";
        if(generate) std::cout << "-g ";
        if(reverse) std::cout << "-r ";
    }

    static void printHelp() {
        std::cout << "Arguments:" << std::endl;
        std::cout << "-h --help                     Prints help" << std::endl;
        std::cout << "-d --dictionary <path>        Sets path to file with dictionary" << std::endl;
        std::cout << "-e --entropy <path>           Sets path to file with entropy" << std::endl;
        std::cout << "-m --mnemonic <path>          Sets path to file with mnemonic" << std::endl;
        std::cout << "-p --password <password>      Sets password" << std::endl;
    }
};

int main(int argc, char** argv) {
    Parser parser(argc, argv);
    parser.printArguments();
}

