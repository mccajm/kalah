/*
 * RandomPlayer.cpp
 *
 *  IPlayer which selects the next move randomly
 */

#include <cstdlib>
#include <iostream>
#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(int n) {
	this->n = n;
	this->board = NULL;
}

vector<int> RandomPlayer::getPossibleMoves() {
    vector<int> possibleMoves;
	for (int i = 1; i < 7; i++) {
		if (this->board->getHouse(i + this->n*this->board->SIDE_WIDTH) > 0) {
			possibleMoves.push_back(i + this->n*this->board->SIDE_WIDTH);
		}
	}

	return possibleMoves;
}

int RandomPlayer::getNextMove(Board *board) {
	this->board = board;
	vector<int> possibleMoves = this->getPossibleMoves();
	if (possibleMoves.size() == 0) {
		return NULL_MOVE;
	}

    int i = rand() % possibleMoves.size();
    return possibleMoves[i];
}

