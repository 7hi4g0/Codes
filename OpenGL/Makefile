GRAPHICS = ../C++/Graphics

all: SimpleTerrain

SimpleTerrain: SimpleTerrain.cpp $(GRAPHICS)/matrix.cpp $(GRAPHICS)/matrix4.cpp
	g++ -o SimpleTerrain SimpleTerrain.cpp $(GRAPHICS)/matrix.cpp $(GRAPHICS)/matrix4.cpp -lX11 -lGL -I $(GRAPHICS)

run: SimpleTerrain
	./SimpleTerrain
