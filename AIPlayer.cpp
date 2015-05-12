/*
 * AIPlayer.cpp
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include "AIPlayer.h"

// TODO: delete each element in transpositionTable

AIPlayer::AIPlayer(int n, Board *board) {
	this->n = n;
	this->board = board;
	this->counter = 0;
}

// Move this into board
vector<int> AIPlayer::getPossibleMoves(Board *b) {
	vector<int> possibleMoves;
	for (int i = 0; i < 6; i++) {
		if (b->getHouse(i + n*7) > 0) {
			possibleMoves.push_back(i + n*7);
		}
	}

	return possibleMoves;
}

int AIPlayer::getNextMove() {
	this->counter = 0;
    int nextMove = -1;
    int bestV = -numeric_limits<double>::max();
    vector<int> possibleMoves = this->getPossibleMoves(this->board);
    for (std::vector<int>::iterator it = possibleMoves.begin() ; it != possibleMoves.end(); ++it) {
    	Board *boardClone = board->clone();
    	boardClone->sowFrom(*it);
    	int v = this->alphaBeta(boardClone, 10000, -numeric_limits<int>::max(), numeric_limits<int>::max(), 1);
    	if (v > bestV) {
    		nextMove = *it;
    	}

    	delete boardClone;
    	this->counter++;
    }

    cout << this->counter << " Nodes traversed" << endl;

    return nextMove;
}

TTEntry *AIPlayer::buildTTEntry(Board *board, int v) {
	TTEntry *tt = new TTEntry();
	// TODO: this needs to be better as we get lots of collisions
	uint64_t low = board->getBoard() >> 32;
	uint64_t high = (board->getBoard() - low) >> 32;
	int h = hash<uint64_t>()(low) ^ (hash<uint64_t>()(high) + 0x9e3779b9 + (low << 6) + (low >> 2));
	tt->key = h ^ v;
	tt->value = v;
	return tt;
}

//alphabeta(origin, depth, -inf, +inf, TRUE)
int AIPlayer::alphaBeta(Board *board, int depth, int alpha, int beta, int maximisingPlayer) {
	if (this->transpositionTable.count(board->getBoard()) > 0) {
		// Do check checksum
		return this->transpositionTable.at(board->getBoard());
	}
	this->counter++;

	if (depth == 0 || (board->getKalah(0) + board->getKalah(1) == board->NUMBER_OF_SEEDS)) {
		return board->getScore();
	}

	int v = -numeric_limits<int>::max();
	vector<int> possibleMoves = this->getPossibleMoves(this->board);
	for (std::vector<int>::iterator it = possibleMoves.begin() ; it != possibleMoves.end(); ++it) {
		Board *boardClone = board->clone();
		boardClone->sowFrom(*it);
		int ab = this->alphaBeta(board, depth-1, alpha, beta, !maximisingPlayer);
		if (maximisingPlayer) {
			if (ab > v) v = ab;
			alpha = (alpha > v) ? alpha : v;
		} else {
			v = -v;
			if (ab < v) v = ab;
			beta = (beta < v) ? beta : v;
		}

		if (beta <= alpha) {
			break; // cut-off
		}

		delete boardClone;
	}

	this->transpositionTable[board->getBoard()] = v;
	return v;
}
