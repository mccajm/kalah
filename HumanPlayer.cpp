/*
 * HumanPlayer.cpp
 *
 *  IPlayer which takes move selection from a human player
 */

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int n) {
	this->n = n;
	this->board = NULL;
}

void HumanPlayer::updatePossibleMoves() {
	this->possibleMoves.clear();
	for (int i = 1; i < this->board->SIDE_WIDTH; i++) {
		if (this->board->getHouse(i + n*this->board->SIDE_WIDTH) > 0) {
			this->possibleMoves.push_back(i + n*this->board->SIDE_WIDTH);
		}
	}
}

/* Query the user for the next move.  If the supplied move is invalid,
 *  query again. */
vector<int>::iterator HumanPlayer::getMoveAsInput() {
    int i;
    vector<int>::iterator it;
    for (;;) {
        cout << ":: Please select a move: ";
        if (cin >> i) {
            it = find(this->possibleMoves.begin(), this->possibleMoves.end(), i);
            if (it != this->possibleMoves.end()) {
               break;
            }

            cout << ":: Please enter a valid move: ";
            for (auto j : this->possibleMoves) {
               	cout << j << " ";
            }

            cout << endl;
        } else {
            cout << ":: Please enter a valid move: ";
            for (auto j : this->possibleMoves) {
            	cout << j << " ";
            }

            cout << endl;
        }
    }

    return it;
}

int HumanPlayer::getNextMove(Board *board) {
	this->board = board;
	this->updatePossibleMoves();
	if (this->possibleMoves.size() == 0) {
		return NULL_MOVE;
	}

    return *getMoveAsInput();
}
