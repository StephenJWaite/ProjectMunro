#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <memory>

//#include "cryptopp/default.h"
//#include "cryptopp/integer.h"

const int MAX_PHRASE_LENGTH=250;

void home();

class Entry {
    private:
    std::string entry;
    std::string username;
    std::string password;
    
    //public member functions
    public:
    Entry(char e[], char u[], char p[]) { // Constructor for Entry class
        entry = e;
        username = u;
        password = p;
    }
};

int main(int argc, char* argv[]) {
 
    char master_pass_phrase [MAX_PHRASE_LENGTH];
       
    if (argc == 1) {
        std::cout << "No database file provided. Creating new password database." << std::endl;
        std::cout << "Please enter a master password to encrypt your password database: ";
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
        exit(1);
    }
}

void home() {

    while (true) {
        std::cout << "Welcome to the best password manager in the world!" << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1) Create new entry" << std::endl;
        std::cout << "2) Retrieve password" << std::endl;
        std::cout << "3) Print all entries" << std::endl;
        std::cout << "4) Save changes and exit" << std::endl;
        std::cout << "5) Discard changes and exit" << std::endl;
        
    }
}
