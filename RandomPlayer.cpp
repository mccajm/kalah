/*
 * RandomPlayer.cpp
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#include <cstdlib>
#include <iostream>
#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(int n, Board *board) {
	this->n = n;
	this->b = board;
}

// Move this into board
vector<int> RandomPlayer::getPossibleMoves() {
    vector<int> possibleMoves;
	for (int i = 1; i < 7; i++) {
		if (this->b->getHouse(i + this->n*this->b->SIDE_WIDTH) > 0) {
			possibleMoves.push_back(i + this->n*this->b->SIDE_WIDTH);
		}
	}

	return possibleMoves;
}

int RandomPlayer::getNextMove() {
	vector<int> possibleMoves = this->getPossibleMoves();
	if (possibleMoves.size() == 0) {
		return -1;
	}

    int i = rand() % possibleMoves.size();
    return possibleMoves[i];
}

