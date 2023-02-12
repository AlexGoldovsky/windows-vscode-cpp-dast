CC = g++
CFLAGS = -fdiagnostics-color=always -Wall -Wvla -Wextra -Werror -static-libgcc -static-libstdc++ -gdwarf-2
TESTFLAGS = -lgtest -lgtest_main

SOURCE = .\Source
INCLUDE = .\Include
TEST = .\Tests

main: main.o utilities.o sort.o
	$(CC) $(CFLAGS) -o main main.o utilities.o sort.o

sort.o: $(INCLUDE)\sort.hpp $(TEST)\Array\test_sort.cpp
	$(CC) $(CFLAGS) -c $(SOURCE)\sort.cpp $(TEST)\Array\test_sort.cpp 

utilities.o: $(INCLUDE)\utilities.hpp
	$(CC) $(CFLAGS) -c $(SOURCE)\utilities.cpp

clean:
	del -recurse -force *.o, *.exe

test_sort: sort.o utilities.o
	$(CC) $(CFLAGS) -o test_sort utilities.o sort.o test_sort.o $(TESTFLAGS)

tests: test_sort
