#ifndef STATE_H
#define STATE_H
#include "Tile.h"
#include<vector>
#include<unordered_map>
using namespace std;

typedef vector<vector<Tile>> Board;

class State
{
    /*
        A State is a combination of various elements.
        It contains a 4x4 Board of Tiles and also the parent 
        State. The Parent State helps to Backtrack. 
        The next possible states (with random tile insertion)
        are calculated and saved in the childrens vector.
    */

private:
    // Dimension of the 2048 Board.
    const int SIZE=4;

    // The Sum that we want to achieve.
    const int GOAL_SUM = 8;

    // Board store the Tiles.
    Board board;

    // A Pointer to the parent State.
    State* parent = NULL;

    // A vector to store the Children/next Possible States with Random Tile inserted.
    vector<State> children;

    // Sum of Tiles in board.
    int sumTiles;

    // Maximum Tile Value in board.
	int maxTileVal;

    // A Map to save the List & Count of Tile Values.
	unordered_map<int,int> frequency_of_tiles;

    // Maximum Attainable Tile Value in one move.
    int maxAttainableTileVal;
    
public:

    // Set up a fresh new game.
    State(); 

    // Makes a new State with the given board configuration and parent.
    State(State* parent, Board board); 

    // Get the Sum of all Tile Values.
    int getSum();

    // Get the maximum Tile Value.
    int maxTileValue();

    // Calculate the List & Count of Tile Values.
    void calcTileValueFreq();

    // Print the List & Count of Tile Values.
    void printTileValueFreq();

    // Add a Random Tile in an empty location on board.
    void addRandom();

    // Returns the resultant board after an Up/Down/Left/Right action on given board.
    Board move(char action, Board board);

    // Finds and stores all the children/next Possible States with Random Tile insertion.
    void generateChildren();

    // Selects and returns a random Child State.
    State* getRandomChild();

    // Returns the States's Parent's address.
    State* getParent();

    // Prints a representation of board.
    void printBoard();

    // Returns true is the Goal State has been achieved.
    bool isGoalState();

    // Clears the Merged Status of all Tiles.
    void clearMerged(Board& board);

    // Updates the maximum attainable value if possible.
    void setMaxAttainableTileValue(int value);

    // Returns the maximum attainable value.
    int getMaxAttainableTileValue();
};

#endif