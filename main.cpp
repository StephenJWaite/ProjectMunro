#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <memory>

#include "picosha2.h" // contains simple SHA-256 hashing function
//#include "cryptopp/dll.h" 
#include "cryptopp/default.h" 

void hash_password(const char* salt, const char* password, std::string& output);
void generate_salt(char* salt);
void unique_pointers();
void encrypt_file (const char* in_file, const char* out_file, const char* pass_phrase);

const int SALT_LENGTH = 8;
const int MAX_PHRASE_LENGTH=250;

class String { // 16 bytes
private:
    char* m_buffer; // 8 bytes
    unsigned int m_size; // 4 bytes

public:
    // Constructor
    String(const char* string) {
        m_size = strlen(string);
        m_buffer = new char [m_size + 1]; // including \0
        memcpy(m_buffer, string, m_size);
        std::cout << "Created String!" << std::endl;
    }

    // Constructor version 2 (no string passed)
    String() {
        std::cout << "Created String!" << std::endl;
        srand(time(NULL)); // Seed the random number generator
        m_size = SALT_LENGTH;
        m_buffer = new char [m_size + 1]; // including \0
        for (int i = 0; i < SALT_LENGTH; i++) {
            sprintf(m_buffer + i, "%x", rand() % 16);
        }
    }

    ~String() {
        std::cout << "Destroyed String!" << std::endl;
    }

    void Print() {
        std::cout << "The buffer points at memory address: " << &m_buffer << std::endl;
    }

    // Copy constructor
    String(const String& other) {
        // Copy the memory from the RHS into "this", a pointer
        // to the object which invoked the function (LHF)
        // sizeof returns the size in bytes of the object.
        // Ours has a char pointer and an unsigned int.

        memcpy(this, &other, sizeof(String)); 
        std::cout << "Copy!\t The String object takes: " << sizeof(String) << " bytes" << std::endl;
    }

    // Overload [] operator to make dereferencing by index possible
    char& operator[](unsigned int index) {
        return m_buffer[index];
    }
    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};


// To use our custom String class with cout, we need to overload the operator
std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream << string.m_buffer; // This tells the << operator to take only m_buffer
    return stream;
}

// char* argv[]: argv is an array of char pointers.
// char* argv: argv is a pointer to the first character of a string array
// char argv[]: argv is an array of characters 
int main(int argc, char* argv[]) {
    //const char password[] = "mypassword";
    char pass_phrase [MAX_PHRASE_LENGTH];
    char salt [SALT_LENGTH] = "invalid";
    std::string hex_hashed_salt_pw;

    String salt_alt; // Create
    String tmp = salt_alt; // Copy
       

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

    //encrypt_file(argv[1], argv[1], pass_phrase);
    
    generate_salt(salt);
    
    hash_password(salt, pass_phrase, hex_hashed_salt_pw);

    unique_pointers();

} // Here the strings go out of scope and so are destroyed

void hash_password(const char* salt, const char* password, std::string& output) {
    
    std::string hash_input;

    hash_input.append(salt);
    hash_input.append(password);

    std::vector<unsigned char> hash_object(picosha2::k_digest_size);
    picosha2::hash256(hash_input.begin(), hash_input.end(), hash_object.begin(), hash_object.end());

    picosha2::bytes_to_hex_string(hash_object, output);

    std::cout << "Salt: " << salt << std::endl;
    std::cout << "Hash input: " << hash_input << std::endl;
    std::cout << "Hash output: " << output << std::endl;
}

void generate_salt(char* salt) {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < SALT_LENGTH; i++) {
        sprintf(salt + i, "%x", rand() % 16);
    }
}

// Unique pointers are for when you want a pointer to only
// last for this scope

void unique_pointers() {
        // Create new scope:
    std::cout << "Unique pointers: " << std::endl;
    {           // Allocate memory on the heap with new
        std::unique_ptr<String> my_string_uniq_ptr(new String("woohoo"));
        // alternative way to call it, c++14:
        std::unique_ptr<String> my_string_uniq_ptr2 = std::make_unique<String>("woohoo");
        my_string_uniq_ptr->Print(); // Access class functions with ->
        my_string_uniq_ptr2->Print();
        
    }

    std::cout << "Unique pointers: " << std::endl;

    String test = "whippee";
    String* p = &test;
    p->Print();
}

void encrypt_file (const char* in_file, const char* out_file, const char* pass_phrase) {
    
    
}