all: compile link

#compile each file to their object files for linking later
compile:
	g++ -c utils/file.cpp -o bin/file.o
	g++ -c lib/database.cpp -o bin/database.o
	g++ -c lib/login.cpp -o bin/login.o
	g++ -c main.cpp -o bin/main.o

# can use * for selecting all files
# link is to connect all the library files
link:
	g++ bin/*.o -o main

run:
	main.exe

clean:
	rm -rf "./bin/*"