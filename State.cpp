#include "headers/State.h"
#include <random>
#include <iostream>
#include <iomanip>

State::State()
{
	this->board = Board(SIZE, vector<Tile>(SIZE, Tile()));
	addRandom();
	addRandom();
	sumTiles = this->getSum();
	maxTileVal = this->maxTileValue();
	calcTileValueFreq();
}

State::State(State *parent, Board board)
{
	State();
	this->board = board;
	this->parent = parent;
}

int State::getSum()
{
	int sum = 0;
	for (vector<Tile> row : board)
	{
		for (Tile t : row)
		{
			sum += t.getValue();
		}
	}
	return sum;
}

int State::maxTileValue()
{
	int max_value = 0;
	for (vector<Tile> row : board)
	{
		for (Tile t : row)
		{
			max_value = (t.getValue() > max_value) ? t.getValue() : max_value;
		}
	}
	return max_value;
}

void State::calcTileValueFreq()
{
	for (vector<Tile> row : board)
	{
		for (Tile t : row)
		{
			if (!t.isEmpty())
			{
				frequency_of_tiles[t.getValue()]++;
			}
		}
	}
}

void State::printTileValueFreq()
{
	if (this->frequency_of_tiles.size() == 0)
	{
		this->calcTileValueFreq();
	}
	for (auto it : this->frequency_of_tiles)
	{
		int val = it.first;
		int f = it.second;
		cout << "There are " << f << " " << val << "s.\n";
	}
	return;
}

void State::addRandom()
{
	vector<pair<int, int>> empty_tiles;
	int length = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j].isEmpty())
			{
				empty_tiles.push_back(make_pair(i, j));
			}
		}
	}

	length = empty_tiles.size();

	if (length > 0)
	{
		int random_idx = rand() % length;
		int x = empty_tiles[random_idx].first;
		int y = empty_tiles[random_idx].second;
		board[x][y] = (rand() % 10 == 0) ? 4 : 2;
	}
}

Board State::move(char action, Board board)
{
	int count, yIncr, xIncr;
	switch (action)
	{
	case 'U':
		count = 0, yIncr = -1, xIncr = 0;
		break;
	case 'D':
		count = SIZE * SIZE - 1, yIncr = 1, xIncr = 0;
		break;
	case 'L':
		count = 0, yIncr = 0, xIncr = -1;
		break;
	case 'R':
		count = SIZE * SIZE - 1, yIncr = 0, xIncr = 1;
		break;
	}

	bool moved = false;

	for (int i = 0; i < SIZE * SIZE; i++)
	{
		int j = abs(count - i);

		int r = j / SIZE;
		int c = j % SIZE;

		if (board[r][c].isEmpty())
			continue;

		int nextR = r + yIncr;
		int nextC = c + xIncr;

		while (nextR >= 0 && nextR < SIZE && nextC >= 0 && nextC < SIZE)
		{
			Tile *next = &board[nextR][nextC];
			Tile *curr = &board[r][c];

			if (next->isEmpty())
			{
				board[nextR][nextC].setValue(curr->getValue());
				board[r][c] = Tile();
				r = nextR;
				c = nextC;
				nextR += yIncr;
				nextC += xIncr;
				moved = true;
			}
			else if (next->canMergeWith(*curr))
			{
				int val = next->mergeWith(*curr);
				setMaxAttainableTileValue(val);
				board[r][c].setValue(0);
				moved = true;
				break;
			}
			else
				break;
		}
	}

	if (moved)
	{
		clearMerged(board);
	}
	return board;
}

void State::clearMerged(Board &board)
{
	for (vector<Tile> row : board)
	{
		for (Tile t : row)
		{
			if (!t.isEmpty())
			{
				t.setMerged(false);
			}
		}
	}
}

void State::generateChildren()
{
	if (this->children.size() != 0)
	{
		return;
	}

	char actions[] = {'U', 'D', 'L', 'R'};
	int insert_values[] = {2, 4};
	this->maxAttainableTileVal = 0;

	for (char action : actions)
	{
		Board temp = move(action, board);

		for (int value : insert_values)
		{
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (temp[i][j].isEmpty())
					{
						temp[i][j].setValue(value);
						children.push_back(State(this, temp));
						temp[i][j].setValue(0);
					}
				}
			}
		}
	}
}

State *State::getRandomChild()
{
	int len = children.size() / 2;
	int random_idx = (rand() % len) + ((rand() % 10 == 0) ? len : 0);
	return &children[random_idx];
}

void State::setMaxAttainableTileValue(int value)
{
	this->maxAttainableTileVal = max(this->maxAttainableTileVal, value);
}

int State::getMaxAttainableTileValue()
{
	if (this->children.size() == 0)
		this->generateChildren();
	return this->maxAttainableTileVal;
}

State *State::getParent()
{
	return this->parent;
}

void State::printBoard()
{
	for (vector<Tile> row : board)
	{
		cout << "+------+------+------+------+" << endl
			 << "| ";
		for (Tile t : row)
		{
			if (t.isEmpty())
				cout << setw(4) << " ";
			else
				cout << setw(4) << t.getValue();
			cout << " | ";
		}
		cout << endl;
	}
	cout << "+------+------+------+------+" << endl
		 << endl;
}

bool State::isGoalState()
{
	this->sumTiles = this->getSum();
	return this->sumTiles == GOAL_SUM;
}
