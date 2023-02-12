CC = g++
CFLAGS = -IInclude -fdiagnostics-color=always -Wall -Wvla -Wextra -Werror -static-libgcc -static-libstdc++ -gdwarf-2
TESTFLAGS = -lgtest -lgtest_main

SOURCE = .\Source
INCLUDE = .\Include
TEST = .\Tests

# source
main: main.o utilities.o sort.o
	$(CC) $(CFLAGS) -o main main.o utilities.o sort.o

sort.o: $(INCLUDE)\sort.hpp $(TEST)\Array\test_sort.cpp
	$(CC) $(CFLAGS) -c $(SOURCE)\sort.cpp $(TEST)\Array\test_sort.cpp 

graph.o: $(INCLUDE)\graph.hpp $(TEST)\Graph\test_graph.cpp
	$(CC) $(CFLAGS) -c $(SOURCE)\graph.cpp $(TEST)\Graph\test_graph.cpp 

utilities.o: $(INCLUDE)\utilities.hpp
	$(CC) $(CFLAGS) -c $(SOURCE)\utilities.cpp

# tests

test_sort: sort.o utilities.o
	$(CC) $(CFLAGS) -o test_sort utilities.o sort.o test_sort.o $(TESTFLAGS)

test_graph: graph.o utilities.o
	$(CC) $(CFLAGS) -o test_graph utilities.o graph.o test_graph.o $(TESTFLAGS)

tests: test_sort test_graph

clean:
	del -recurse -force *.o, *.exe