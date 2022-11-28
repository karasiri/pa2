CXX=g++
LD=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
CLIB=`sdl2-config --cflags --libs` -lSDL2
BIN=./karasiri/

all: compile doc

compile: main.o graphics.o block.o key.o fish.o shark.o health.o spike.o door.o wall.o level.o game.o
	$(LD) -o karasiri $^ `sdl2-config --cflags --libs` -lSDL2
	rm -f *.o

%o: src/%cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CLIB)
	
clean:
	rm -f program *.o 
	rm -rf karasiri
	rm -rf doc
	
run:
	./karasiri
	
doc:
	doxygen
