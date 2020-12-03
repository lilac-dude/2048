#ifndef TILE_H
#define TILE_H
#include <stdint.h>

class Tile
{
    /*
        A Tile is a basic block of the 
        2048 Puzzle. The 2048 Puzzle board 
        is a grid consisting of 4x4 = 16 Tiles.
    */
   
private:
    // Value stored in the Tile.
    int value = 0;
    // Used to check if a Tile has already been merged.
    bool merged = false;

public:
    Tile();
    Tile(int value);

    // returns true if value = 0: The tile is empty.
    bool isEmpty(); 

    // Get the value of Tile.
    int getValue();

    // Set the value of Tile.
    void setValue(int value);

    // returns true if possible to merge with other Tile.
    bool canMergeWith(Tile other); 

    // merges the other Tile into this Tile if possible and returns new value. Else returns -1.
    int mergeWith(Tile other);     

    // sets the merged value as m.
    void setMerged(bool m);
};

#endif