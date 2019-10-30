# PA193_mnemonic_SIGSEGVboys
Autumn 2019 semester project for PA193

[![Build Status](https://travis-ci.org/Gariane/PA193_mnemonic_SIGSEGVboys.svg?branch=master)](https://travis-ci.org/Gariane/PA193_mnemonic_SIGSEGVboys)
[![codecov](https://codecov.io/gh/Gariane/PA193_mnemonic_SIGSEGVboys/branch/master/graph/badge.svg)](https://codecov.io/gh/Gariane/PA193_mnemonic_SIGSEGVboys)

Description
===========

Implements generation of mnemonic sentence as defined in BIP39 [Bitcoin Improvement Proposal 39]. Written in
C++, the implementation provides 3 basic functionalities:
 1. generation of mnemonic seed and phrase from input entropy
 2. generation of seed and initial entropy from mnemonic phrase
 3. checking if given mnemonic phrase generates given seed

The implementation itself (not counting tests) consists of two components: the library and the CLI. The library
defines and implements API for usage in other projects. CLI provides demonstration of the library's functionality
using command line arguments.

    [Bitcoin Improvement Proposal 39]: https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki

Usage
=====

### Prerequisites

 1. C++ compiler supporting at least `c++17`
 2. `CMake`, version at least 3.0
 3. `OpenSSL` library

Building the CMake projects creates three files - a `bip39` library, a `cli`, and
`testsuite`.

### BIP39 library

API is described in the header files `dictionary.hpp` and `mnemonic.hpp`.

### CLI usage
