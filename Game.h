#ifndef GAME_H
#define GAME_H
#include "State.h"
#include<unordered_set>

class Game
{
private:
    State* currState;
    unordered_set<State*> visited;
    bool has_won = false;
public:
    Game();
    bool hasFinished();
    void printBoard();
    
};

#endif

