#include <iostream>

#include "cryptopp/modes.h" // CFB_Mode
#include "cryptopp/aes.h" // Advanced Encryption Standard
#include "cryptopp/osrng.h" // Random number generator

const int MAX_PHRASE_LENGTH=250;

void home();

class Entry {
    private:
    std::string name;
    std::string username;
    std::string password;
    
    //public member functions
    public:
    Entry(const char e[],const char u[],const char p[]) { // Constructor for Entry class
        name = e;
        username = u;
        password = p;
    }
};

int main(int argc, char* argv[]) {
 
    // Allocate 250 bytes on the stack (std::string would go on the heap,
    // and would be slower to access. Since our "string" doesn't need to
    // change in any way, char (c-string) is the better option
    char master_pass_phrase [MAX_PHRASE_LENGTH];
       
    if (argc == 1) {
        std::cout << "No database file provided. Creating new password database." << std::endl;
        std::cout << "Please enter a master password to encrypt your password database: ";
        // cin.getline reads input from the stream into a c-string.
        // It reads MAX_PHRASE_LENGTH characters from the input steam or until it hits \n
        std::cin.getline(master_pass_phrase, MAX_PHRASE_LENGTH);
        home();
    }
    else if (argc == 2) {
        std::cout << "Database file found. Please enter your password: ";
        std::cin.getline(master_pass_phrase, MAX_PHRASE_LENGTH);
        home();
    }
    else {
        std::cout << "Incorrect usage. Aborting" << std::endl;
        exit(1); // We can't recover from this, so exit. Alternatively: default to create new db
    }


    // Initialise the object to generate random data
    CryptoPP::AutoSeededRandomPool rnd;

    // The "Initialisation Vector" is used as a parameter
    // during encryption, it acts like a "salt" for passwords, i.e.
    // it ensures the ciphertext created when encrypting a file is
    // different every time, even if the file contents doesn't change.
    // This means we need to store the IV for later decryption
    // The IV and the key both need to be 16 bytes, specified by the
    // CryptoPP::AES::BLOCKSIZE, which is just an int = 16.
    // CryptoPP::SecByteBlock... creates a secure block of byte data
    // called "iv" which is 16 bytes long. A single memory address
    // holds one byte.
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    rnd.GenerateBlock(iv, iv.size());

    // The keylength must also be 16 bytes
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key, key.size());

    // byte = unsigned char = 8 bit, stack allocated data
    // yes this is retarded, in Rust this is type [u8].
    // 8 bits unsigned is the ranged 0 to 127
    const unsigned char plain_text[] = "Hellö! How are you."; // one char = one byte only applies to ASCII. Try ö
    size_t message_len = std::strlen((char*)plain_text) + 1;

    std::cout << "The plain text is " << message_len << "bytes long" << std::endl;
    /*
    CryptoPP::CFB_Mode -> Class Template
    Cipher Feedback mode of operation.
    A block cipher by itself is only suitable for the secure cryptographic
    transformation (encryption or decryption) of one fixed-length group of
    bits called a block.[2] A mode of operation describes how to repeatedly
    apply a cipher's single-block operation to securely transform amounts
    of data larger than a block.

    CryptoPP::AES -> This is our block cipher. It encrypts/decrypts 16 bytes
    or 128 bits at a time.

    The angle brackets mean CFB_Mode takes AES as a template parameter

    "Encryption" is one of two members of enumerator CipherDir: "Decryption
    is the other".
    */
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor;
    
}

void home() {

    while (true) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Welcome to the best password manager in the world!" << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1) Create new entry" << std::endl;
        std::cout << "2) Retrieve password" << std::endl;
        std::cout << "3) Print all entries" << std::endl;
        std::cout << "4) Save changes and exit" << std::endl;
        std::cout << "5) Discard changes and exit" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        
        // Get user input, making sure they entered an integer
        int user_choice;
        
        std::cin >> user_choice; // 5\n is in the stream, cin parses 5 into user choice
                
        while(std::cin.fail() || user_choice > 5) { // Loop until valid integer entered
            std::cout << "Please enter an integer:" << std::endl;
            std::cin.clear(); // Clears the error flag, NOT the stream
            std::cin.ignore(256,'\n'); // abc\n is in the stream, move forward 256 chars or until we reach \n:   .abc\n -> a.bc\n  -> ab.c\n -> abc.\n
            std::cin >> user_choice; // cin knows to ignore \n when parsing to an integer
        }

        // This is syntax sugar for if...elseif...elseif.
        switch(user_choice) {
            case 1: {
                std::cout << "Now do something" << std::endl;
                return;
            }
            case 2: {
                std::cout << "Now do something" << std::endl;
                return;
            }
            case 3: {
                std::cout << "Now do something" << std::endl;
                return;
            }
            case 4: {
                std::cout << "Now do something" << std::endl;
                return;
            }
            case 5: {
                std::cout << "Now do something" << std::endl;
                return;
            }
        }   
    }
}