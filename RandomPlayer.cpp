/*
 * RandomPlayer.cpp
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#include <cstdlib>
#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(int n, Board *board) {
	this->n = n;
	this->board = board;
}

RandomPlayer::~RandomPlayer() {
	// TODO Auto-generated destructor stub
}

void RandomPlayer::updatePossibleMoves() {
	this->possibleMoves.clear();
	for (int i = 0; i < 6; i++) {
		if (this->board->getHouse(i + n*7) > 0) {
			this->possibleMoves.push_back(i + n*7);
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
