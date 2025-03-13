CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: lib/dijkstras_main

lib/dijkstras_main: src/dijkstras_main.cpp lib/dijkstras.o
	g++ $(CXXFLAGS) src/dijkstras_main.cpp -o lib/dijkstras_main lib/dijkstras.o
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes ./lib/dijkstras_main

lib/dijkstras.o: src/dijkstras.cpp
	g++ $(CXXFLAGS) -c src/dijkstras.cpp -o lib/dijkstras.o

clean:
	rm -f lib/dijkstras_main lib/*.o
