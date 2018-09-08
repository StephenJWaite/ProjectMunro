#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <memory>
#include "picosha2.h"

void hash_password(const char* salt, const char* password, std::string& output);
void generate_salt(char* salt);
void unique_pointers();

const int SALT_LENGTH = 8;

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
        std::cout << "The buffer points at memory address: " << m_buffer << std::endl;
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

void generate_salt_alt(String&);

// To use our custom String class with cout, we need to overload the operator
std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream << string.m_buffer; // This tells the << operator to take only m_buffer
    return stream;
}


int main(void) {
    const char password[] = "mypassword";
    char salt [SALT_LENGTH] = "invalid";
    std::string hex_hashed_salt_pw;

    String salt_alt; // Create
    String tmp = salt_alt; // Copy
    //String* ptr = &salt_alt;

    //ptr->Print(); // This is how pointers access fns
    //salt_alt.Print();
    
    generate_salt(salt);
    
    // std::cout << "Salt alt: " << salt_alt << std::endl;
    
    hash_password(salt, password, hex_hashed_salt_pw);

    unique_pointers();

    int a = 4;
    int* b = &a;
    std::cout << b << std::endl;

    const char* c = "welp";
    std::string d = c;
    std::cout << &d << std::endl;


} // Here the strings go out of scope and so are destroyed

void hash_password(const char* salt, const char* password, std::string& output) {
    
    std::string hash_input;

    hash_input.append(salt);
    hash_input.append(password);

    std::vector<unsigned char> hash_object(picosha2::k_digest_size);
    picosha2::hash256(hash_input.begin(), hash_input.end(), hash_object.begin(), hash_object.end());

    picosha2::bytes_to_hex_string(hash_object, output);

    // std::cout << "Salt: " << salt << std::endl;
    // std::cout << "Hash input: " << hash_input << std::endl;
    // std::cout << "Hash output: " << output << std::endl;
}

void generate_salt(char* salt) {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < SALT_LENGTH; i++) {
        sprintf(salt + i, "%x", rand() % 16);
    }
}

// Potential objects:
// Salt - hex string
// Password - utf8 string
// Input hash - string
// Output hash - string

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
        
    }

    std::cout << "Unique pointers: " << std::endl;

    String test = "whippee";
    String* p = &test;
    p->Print();

}