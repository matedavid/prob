// File with all the codification related functions

#include "../header/codification.h"

std::string encode(std::string& toEncode) {
    std::string encoded;
    for (int i = 0; i < toEncode.length(); i++) {
        encoded += toEncode[i] ^ key;
    }
    return encoded;
}

std::string decode(std::string toDecode) {
    std::string decoded;
    for(int i = 0; i < toDecode.length(); i++) {
        decoded += toDecode[i] ^ key;
    }
    return decoded;
}

