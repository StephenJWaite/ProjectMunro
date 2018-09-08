# ProjectMunro
Its a munro style project

We dont even know how to use git, life is pain

---------------------------------------------
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
