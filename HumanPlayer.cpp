/*
 * HumanPlayer.cpp
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int n, Board *board) {
	this->n = n;
	this->board = board;
}

// Move this into board
void HumanPlayer::updatePossibleMoves() {
	this->possibleMoves.clear();
	for (int i = 1; i < this->board->SIDE_WIDTH; i++) {
		if (this->board->getHouse(i + n*this->board->SIDE_WIDTH) > 0) {
			this->possibleMoves.push_back(i + n*this->board->SIDE_WIDTH);
		}
	}
}

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

            cout << endl << endl;
        } else {
            cout << ":: Please enter a valid move: ";
            for (auto j : this->possibleMoves) {
            	cout << j << " ";
            }

            cout << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return it;
}

int HumanPlayer::getNextMove() {
	this->updatePossibleMoves();
	if (this->possibleMoves.size() == 0) {
		return -1;
	}

    return *getMoveAsInput();
}
