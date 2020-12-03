#include "headers/State.h"
#include <unordered_set>
#include <iostream>
using namespace std;

#define GOAL_SUM 8

int main()
{   
    srand(time(NULL));
 
    // Fresh new Game State. Has only 2 positions filled, rest are all empty.
    State *currState = new State();

    // Set of Visited States to help avoid repeated computations.
    unordered_set<State *> visited;

    // Loop Until We reach the Goal State.
    while (!currState->isGoalState())
    {   
        // Print the current State's Board.
        currState->printBoard();

        // Check if the Sum of current State overshoots the Goal sum.
        if (currState->getSum() > GOAL_SUM)
        {   
            // Backtrack.
            cout << "Sum > 8, Backtracking to previous state!\n\n\n";
            // Go back to parent state.
            currState = currState->getParent();
            continue;
        }

        // Generate the children/next possible states if not already computed.
        if (visited.find(currState) == visited.end())
        {   
            // Generate Children.
            currState->generateChildren();

            // Add the current State to the set of visited States.
            visited.insert(currState);
        }

        // Printing State-->Z operations.
        cout <<"Sum of Tile Values: " << currState->getSum() << endl;
        cout << "Max Tile Value: " <<  currState->maxTileValue() << endl;
        cout << "Max Attainable Tile Value: " << currState->getMaxAttainableTileValue() << endl;
        cout << "List & Count of Tile Values-\n";
        currState->printTileValueFreq();
        cout << endl << endl;

        // Go to the nextState/ChildState.
        currState = currState->getRandomChild();
    }

    // Print the Final Board.
    currState->printBoard();
    cout << "Goal State Achieved!\n";
    return 0;
}