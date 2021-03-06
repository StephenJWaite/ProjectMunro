# ProjectMunro

## Setup

### Install libaries:

```
	sudo apt install libcrypto++-dev libcrypto++-doc libcrypto++-utils
```
Header files are installed to /usr/include/crypto++/

The .so and .a files are installed to /usr/lib/x86_64-linux-gnu/

The .a (archive) file is a "static" library

.so (shared object) files are shared objects or dynamic libraries, similar to DLL on Windows.

Static libraries are compiled into the binary.

Dynamic libraries are accessed at runtime.

### Library documentation:

```
	firefox /usr/share/doc/libcrypto++-doc/html/index.html &
```
### Compile

```
	g++ main.cpp -o run -l:libcryptopp.a && ./run
```

### Objectives
The aim of this project is to create a C++ imlpementation
of a password manager. The user should be able to create new
entries with a username and password. The program encrypts 
the input and saves it to the database.

A master password is required in order to decrypt the database
file, so that the user can retrieve their desired password. This
master password functions as the key which is used to encrypt
or decrypt each password entry.

The user should be able to search entries in the database.
Each entry contains a title "Facebook", a username/email,
and the encrypted password.

We can also implement a password DB which is typical of websites,
i.e. we don't store the encrypted password, but instead the hashed
salted password. This is more secure since we don't have any private
key/encryption key to lose.

### Workflow
The user runs the binary optionally with a single argument representing
an encrypted file.

#### Case 1): No argument
The user is prompted to enter a the name of their database file and a
new master password, with which the database file will be encrypted.

Subsequently, the user reaches a "home" screen, where they are prompted
to choose between several possible actions such as "create new entry",
"display all entries", "print individual password to screen", "save and exit",
"exit without saving".

#### Case 2): Single argument provided
If the user provides an argument to the command line binary call, the program
will immediately attempt to decrypt the file, first prompting the user for
the key (password) with which it was encrypted. If decryption was successful,
we will be able to load the contents of the file into our custom "Entry" class.
If this fails, the database is either corrupt or the provided password was incorrect.

Once the database file has been successfully decrypted, we proceed to the same
"home" screen mentioned above in Case 1.

### Classes
I propose a custom class called "Entry", which contains three std::string objects;
"title/entry/name/whatever", "Account/username", "password". Before encryption,
the data will need to be converted into, for example, CSV format. This class would
also contain the methods relevant to handling database entries.

### Getting started
A good starting point would be to lay out the structure of main.cpp, including the
home screen functionality, as well as to define the Entry class.

For now we can hard code the input data for encryption decryption for faster iterating.
Then we need to figure out how to interface with the cryptopp library regarding file
encryption/decryption.

### VS Code Setup

Get ligatures:
```
	sudo apt install fonts-firacode
```
In VS Code, hit
```
	ctrl+,
```
to open settings. Search for "font", and then replace the contents of "font family"
with
```
	'Fira Code'
```
and check the box to use ligatures.

#### Command palette
To open the command palette, hit:
```
	ctrl+shift+p
```

You can change the theme, git commit/push etc. and many other things
with the palette.

#### Opening workspace from terminal
Navigate to ProjectMunro and then use:
```
	code .
```
This keeps everything together including config files, rather than opening
files individually.

#### Debugging
On Linux, typically the GNU GDB debugger is used.
To work properly, we need to pass g++ the -g flag.
Then breakpoints can be set in VS Code and we can hit F5
to debug.

On first attempt, change the JSON to point to the binary
compiled with -g, e.g. "${workspaceFolder}/a.out"
or "${workspaceFolder}/run"