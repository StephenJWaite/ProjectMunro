#include "password_manager.h"

// TIL: There is literally only one difference between a class and a struct:
// Classes: every member and method is default private
// Struct: every member and method is default public
// In practice, most people use struct to represent P.O.D.,
// and class where we want to write methods.
class Entry {
    private:
    // The encryption functions deal with blocks of memory (addresses) at a time.
    // Under the hood, they work by flipping a fixed number of bits at a time
    // in some voodoo way.
    // Almost all modern computers are byte-addressable, meaning each
    // individual memory address holds one byte of data, i.e. 8 bits.
    // 8 bits can hold 2^8 possible values. The type char ranges from -128 to 127
    // in value. The type unsigned char ranges from 0 to 255 in value.
    
    // byte (type) is inside cryptopp/config.h, and is in the global namespace, not CryptoPP
    // "byte" is short for "unsigned char", as "size_t" is short for "unsigned int"
    const byte* name;
    const byte* username;
    const byte* password;

    
    public:

    // Here, static means that MAX_USERNAME_LENGTH is not a member
    // of any specific instance of Entry, like name etc. Instead,
    // it is shared across all instances, and can be accessed
    // like this: Entry::MAX_USERNAME_LENGTH, or from an individual
    // class instance (object) -> entry.MAX_USERNAME_LENGTH
    static const short int MAX_USERNAME_LENGTH = 30;

    // Entry(const char* e, const char* u, const char* p) { // Constructor for Entry class
    //     name = e;
    //     username = u;
    //     password = p;
    // }

    // Using an initialisation list, we can make make our object's attributes "const".
    Entry(const byte* e, const byte* u, const byte* p)
        : name(e), username(u), password(p) {} // Constructor
    
    // Destructor
    // We need to delete any raw pointers (*) to free memory
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
    }
    else if (argc == 2) {
        std::cout << "Database file found. Please enter your password: ";
        std::cin.getline(master_pass_phrase, MAX_PHRASE_LENGTH);
        
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
    const byte plain_text[] = "Facebook,a.n_munro@outlook.com,my_password\n"; // one char = one byte only applies to ASCII. Try ö

    // Add 1 because strlen ignores null terminator \0
    size_t message_len = std::strlen((char*)plain_text) + 1; // size_t is simply a typedef for unsigned long = unsigned int
    byte encrypted_data[2*message_len];

    std::cout << "The plain text is " << message_len << " bytes long" << std::endl;
    std::cout << "Plain text in bytes: " << std::endl;
    print_byte_array_as_decimal(plain_text);
    byte cipher_text[message_len];

    while (true) {
        
        print_home_screen();
        // Get user input, making sure they entered an integer
        unsigned short user_choice; // int is overkill.
        
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
                return 0;
            }
            case 2: {
                std::cout << "Now do something" << std::endl;
                return 0;
            }
            case 3: {
                std::cout << "Now do something" << std::endl;
                return 0;
            }
            case 4: {
                encrypt(iv, key, plain_text, message_len, encrypted_data);
                return 0;
            }
            case 5: {
                std::cout << "Call decrypt for testing" << std::endl;
                //decrypt(iv, key, cipher_text, )
            }
        }   
    }
}

void encrypt(const CryptoPP::SecByteBlock& iv,
             const CryptoPP::SecByteBlock& key,
             const byte* plain_text,
             const int& message_len, // The "message" is our entire file
             byte* encrypted_data
             ) {

    byte ciphertext[2*message_len];
    byte decrypted_ciphertext[message_len];
    /*
    CryptoPP::CFB_Mode -> Class Template
    Cipher Feedback mode of operation.
    A block cipher by itself is only suitable for the secure cryptographic
    transformation (encryption or decryption) of one fixed-length group of
    bits called a block. A mode of operation describes how to repeatedly
    apply a cipher's single-block operation to securely transform amounts
    of data larger than a block.

    CryptoPP::AES -> This is our block cipher. It encrypts/decrypts 16 bytes
    or 128 bits at a time.

    The angle brackets mean CFB_Mode takes AES as a template parameter.

    "Encryption" is one of two members of enumerator CipherDir: "Decryption"
    is the other.
    */
    
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor(key, key.size(), iv);
    encryptor.ProcessData(ciphertext, plain_text, message_len);

}

void decrypt(const CryptoPP::SecByteBlock& iv,
             const CryptoPP::SecByteBlock& key,
             const byte* ciphertext,
             byte* decrypted_ciphertext,
             const int& message_len // The "message" is our entire file
             ) {

    

    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryptor(key, key.size(), iv);
    decryptor.ProcessData(decrypted_ciphertext, ciphertext, message_len);
}

