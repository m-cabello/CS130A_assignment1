# ifndef SHA256_H
# define SHA256_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
using namespace std;
// I utilzied the OpenSSL C++ libraries that provided me with the SHA256 hash function
string sha256(const string str){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

#endif
