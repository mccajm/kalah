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
void RandomPlayer::updatePossibleMoves() {
	this->possibleMoves.clear();
	for (int i = 1; i < 7; i++) {
		if (this->b->getHouse(i + this->n*this->b->SIDE_WIDTH) > 0) {
			this->possibleMoves.push_back(i + this->n*this->b->SIDE_WIDTH);
		}
	}
}

int RandomPlayer::getNextMove() {
	this->updatePossibleMoves();
	if (this->possibleMoves.size() == 0) {
		return -1;
	}

    int i = rand() % this->possibleMoves.size();
    return this->possibleMoves[i];
}

