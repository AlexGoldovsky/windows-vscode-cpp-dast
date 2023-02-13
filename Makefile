CC = g++
CFLAGS = -IInclude -fdiagnostics-color=always -Wall -Wvla -Wextra -Werror -static-libgcc -static-libstdc++ -gdwarf-2
TESTFLAGS = -lgtest -lgtest_main

SOURCE = .\Source
INCLUDE = .\Include
TEST = .\Tests

# source
main: main.o utilities.o array.o
	$(CC) $(CFLAGS) -o main main.o utilities.o array.o

array.o: $(INCLUDE)\array.hpp $(TEST)\Array\test_array.cpp
	$(CC) $(CFLAGS) -c $(SOURCE)\array.cpp $(TEST)\Array\test_array.cpp 

graph.o: $(INCLUDE)\graph.hpp $(TEST)\Graph\test_graph.cpp
	$(CC) $(CFLAGS) -c $(SOURCE)\graph.cpp $(TEST)\Graph\test_graph.cpp 

utilities.o: $(INCLUDE)\utilities.hpp
	$(CC) $(CFLAGS) -c $(SOURCE)\utilities.cpp

# tests

test_array: array.o utilities.o
	$(CC) $(CFLAGS) -o test_array utilities.o array.o test_array.o $(TESTFLAGS)

test_graph: graph.o utilities.o
	$(CC) $(CFLAGS) -o test_graph utilities.o graph.o test_graph.o $(TESTFLAGS)

tests: test_array test_graph

clean:
	del -recurse -force *.o, *.exe