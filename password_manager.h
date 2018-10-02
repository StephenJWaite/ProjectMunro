#include <iostream>
#include "cryptopp/modes.h" // CFB_Mode
#include "cryptopp/aes.h" // Advanced Encryption Standard
//      https://cryptopp.com/wiki/Advanced_Encryption_Standard
#include "cryptopp/osrng.h" // Random number generator

// static means this variable is only available in the scope of this
// header file and any cpp files it is included in. If it weren't
// static, the linker would include it in the entire global setting,
// which is "bad taste".
static const int MAX_PHRASE_LENGTH=250;

void encrypt(const CryptoPP::SecByteBlock& iv,
             const CryptoPP::SecByteBlock& key,
             const byte* plain_text,
             const int& message_len);
void decrypt(const CryptoPP::SecByteBlock& iv,
             const CryptoPP::SecByteBlock& key,
             const byte* ciphertext,
             byte* decrypted_ciphertext,
             const int& message_len // The "message" is our entire file
             );

void print_byte_array_as_decimal(const byte* str) {
    const int length = strlen((char*)str);
    std::cout << "[  ";
    for (int i = 0; i < length; i++) {
        std::cout << (int)str[i] << "  ";
    }
    std::cout << "]" << std::endl;
}

void print_home_screen() {
        std::cout << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Welcome to the best password manager in the world!" << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1) Create new entry" << std::endl;
        std::cout << "2) Retrieve password" << std::endl;
        std::cout << "3) Print all entries" << std::endl;
        std::cout << "4) Save changes and exit" << std::endl;
        std::cout << "5) Discard changes and exit" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << std::endl;
}