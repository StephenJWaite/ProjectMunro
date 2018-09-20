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
    std::string name;
    std::string username;
    std::string password;
    
    //public member functions
    public:
    Entry(char e[], char u[], char p[]) { // Constructor for Entry class
        name = e;
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
        exit(1); // We can't recover from this, so exit. Alternatively: default to create new db
    }
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
            std::cin >> user_choice; // cin knows to ignore when parsing to an integer 
        }

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

// 