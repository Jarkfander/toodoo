all: toodoo

toodoo: main.o
	g++ -o toodoo main.o

main.o: main.cpp
	g++ -o main.o -c main.cpp -W -Wall -ansi -pedantic


clean:
	rm -rf *.o

cleanall: clean
	rm -rf toodoo
