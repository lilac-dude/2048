driver.out: driver.cpp State.o Tile.o
	g++ driver.cpp State.o Tile.o

State.o: State.cpp
	g++ -c State.cpp

Tile.o: Tile.cpp
	g++ -c Tile.cpp

clean:
	rm -f *.o *.out