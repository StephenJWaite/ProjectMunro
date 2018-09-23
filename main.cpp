#include <iostream>

#include "cryptopp/modes.h" // CFB_Mode
#include "cryptopp/aes.h" // Advanced Encryption Standard
//      https://cryptopp.com/wiki/Advanced_Encryption_Standard
#include "cryptopp/osrng.h" // Random number generator

const int MAX_PHRASE_LENGTH=250;

void home();
void encrypt(const CryptoPP::SecByteBlock& iv,
             const CryptoPP::SecByteBlock& key,
             unsigned char* plain_text,
             const int& message_len);
void print_byte_array_as_decimal(const byte* str);

class Entry {
    private:
    // The encryption functions deal with blocks of memory (addresses) at a time.
    // Under the hood, they work by flipping a fixed number of bits at a time
    // in some voodoo way.
    // Almost all modern computers are byte-addressable, meaning each
    // individual memory address holds one byte of data, i.e. 8 bits.
    // 8 bits can hold 2^8 possible values. The type char ranges from -128 to 127
    // in value. The type unsigned char ranges from 0 to 255 in value.
    
    // byte is inside cryptopp/config.h, and is in the global namespace, not CryptoPP
    const byte* name;
    const byte* username;
    const byte* password;
    
    //public member functions
    public:
    // Entry(const char* e, const char* u, const char* p) { // Constructor for Entry class
    //     name = e;
    //     username = u;
    //     password = p;
    // }

    // Using initialisation lists, we can make make our object's
    // attributes "const".
    Entry(const byte* e, const byte* u, const byte* p)
        : name(e), username(u), password(p) {} // Constructor
    
    // Destructor
    // We need to delete any raw pointers (*) to free
    // memory
    ~Entry() {
        delete name;
        delete username;
        delete password;
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
    const byte plain_text[] = "Hello! How are you."; // one char = one byte only applies to ASCII. Try ö

    // Add 1 because strlen ignores null terminator \0
    size_t message_len = std::strlen((char*)plain_text) + 1; // size_t is simply a typedef for unsigned long = unsigned int
    size_t msg_len2 = sizeof(plain_text); // This is the same as above
    std::cout << "The plain text is " << message_len << " bytes long" << std::endl;
    std::cout << "Plain text in bytes: " << std::endl;
    print_byte_array_as_decimal(plain_text);
    byte cipher_text[message_len];

    
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
            //encrypt();
            return;
        }
        case 5: {
            std::cout << "Now do something" << std::endl;
            return;
        }
    }   
       
    }
}

void encrypt(const CryptoPP::SecByteBlock& iv,
             const CryptoPP::SecByteBlock& key,
             unsigned char* plain_text,
             const int& message_len) {

    
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

    The angle brackets mean CFB_Mode takes AES as a template parameter.

    "Encryption" is one of two members of enumerator CipherDir: "Decryption"
    is the other.
    */

    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor(key, key.size(), iv);
    encryptor.ProcessData(plain_text, plain_text, message_len);
}

void print_byte_array_as_decimal(const byte* str) {
    const int length = strlen((char*)str);
    std::cout << "[  ";
    for (int i = 0; i < length; i++) {
        std::cout << (int)str[i] << "  ";
    }
    std::cout << "]" << std::endl;
}