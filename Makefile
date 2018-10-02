

# when main.o changes, run the following command to produce "run"
run: main.o
	g++ main.o -o run -l:libcryptopp.a

# when main.cpp changes, run the following command to produce "main.o"
# -c flag simply compiles into an object file
main.o: main.cpp
	g++ -c main.cpp

# doesn't produce anything, but we can invoke from terminal
clean:
	rm *.o

###### SCHEMA
# target: dependencies
#	  action