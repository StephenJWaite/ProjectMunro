#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <memory>

#include "cryptopp/default.h"
#include "cryptopp/integer.h"

void hash_password(const char* salt, const char* password, std::string& output);
void generate_salt(char* salt);

const int SALT_LENGTH = 8;
const int MAX_PHRASE_LENGTH=250;

// char* argv[]: argv is an array of char pointers.
// char* argv: argv is a pointer to the first character of a string array
// char argv[]: argv is an array of characters 
int main(int argc, char* argv[]) {
    
    char pass_phrase [MAX_PHRASE_LENGTH];
            
    CryptoPP::Integer i;
       
    if (argc == 1) {
        std::cout << "No database file provided. Creating new password database." << std::endl;
        std::cout << "Please enter a master password to encrypt your password database: ";
        std::cin.getline(pass_phrase, MAX_PHRASE_LENGTH);
    }
    else if (argc == 2) {
        std::cout << "Database file found. Please enter your password: ";
        std::cin.getline(pass_phrase, MAX_PHRASE_LENGTH);
    }
    else {
        std::cout << "Incorrect usage. Aborting" << std::endl;
        exit(1);
    }
 
} 
