/*
 * AIPlayer.cpp
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <ctime>
#include "AIPlayer.h"

AIPlayer::AIPlayer(int n, Board *board) {
	this->n = n;
	this->board = board;
	this->counter = 0;
	// ~7MB preallocated to prevent repetitive malloc()
	this->transpositionTable.reserve(409600);
}

// Move this into board
vector<int> AIPlayer::getPossibleMoves(Board *b) {
	vector<int> possibleMoves;
	for (int i = 1; i < 7; i++) {
		if (b->getHouse(i + this->n*7) > 0) {
			possibleMoves.push_back(i + this->n*7);
		}
	}

	return possibleMoves;
}

int AIPlayer::getNextMove() {
	this->counter = 0;
    if (this->getPossibleMoves(this->board).size() == 0) {
        return -1;
    }

    // Iterative Deepening
    int bestMove = -1;
    clock_t start = clock();
    double duration = 0;
    for (int depth = 1; depth < 100000; depth++) {
    	bestMove = this->mtdf(this->getPossibleMoves(this->board).at(0), depth);
    	duration = std::clock() - start / (double)CLOCKS_PER_SEC;
    	if (duration > 2) {
    		break;
    	}
    }

    cout << this->counter << " Nodes traversed" << endl;
    this->transpositionTable.clear();

    return bestMove;
}

TTEntry *AIPlayer::buildTTEntry(Board *board, int v) {
	TTEntry *tt = new TTEntry();
	// TODO: this needs to be better as we get lots of collisions
	uint64_t low = board->getBoard() >> 64;
	uint64_t high = (board->getBoard() - low) >> 64;
	int h = hash<uint64_t>()(low) ^ (hash<uint64_t>()(high) + 0x9e3779b9 + (low << 6) + (low >> 2));
	tt->key = h ^ v;
	tt->value = v;
	return tt;
}

int AIPlayer::mtdf(int f, int depth) {
	int bestMove = f;
	int upperBound = numeric_limits<int>::max();
	int lowerBound = -numeric_limits<int>::max();
	while (lowerBound < upperBound) {
	    int beta = f;
	    if (f == lowerBound) {
	    	beta++;
	    }

	    f = this->alphaBeta(this->board, depth, beta-1, beta, (this->n == 0), &bestMove);
	    if (f < beta) {
	    	upperBound = f;
	    } else {
	    	lowerBound = f;
	    }
	}

	return bestMove;
}

//alphabeta(origin, depth, -inf, +inf, TRUE)
int AIPlayer::alphaBeta(Board *board, int depth, int alpha, int beta, int maximisingPlayer, int *bestMove) {
	if (this->transpositionTable.count(board->getBoard()) > 0) {
		// Do check checksum
		return this->transpositionTable.at(board->getBoard());
	}

	this->counter++;
	if (depth == 0 || (board->getKalah(0) + board->getKalah(1) == board->NUMBER_OF_SEEDS*2)) {
		return board->getScore();
	}

	int bestValue = -numeric_limits<int>::max();
	vector<int> possibleMoves = this->getPossibleMoves(board);
	for (int i = 0; i < (int)possibleMoves.size(); i++) {
		Board *boardClone = board->clone();
		int lastHouse = boardClone->sowFrom(possibleMoves[i]);
		vector<int> houses = this->board->getHouses(maximisingPlayer); // FIX
		if (find(houses.begin(), houses.end(), lastHouse) != houses.end()) {
			maximisingPlayer = !maximisingPlayer;
		}

        if ((int)this->getPossibleMoves(boardClone).size() == 0) {
        	boardClone->endGame();
    		return board->getScore();
        }

		int ab = this->alphaBeta(boardClone, depth-1, alpha, beta, !maximisingPlayer, bestMove);
		if (maximisingPlayer) {
			if (ab > bestValue) {
				bestValue = ab;
				*bestMove = possibleMoves[i];
			}
			alpha = (alpha > bestValue) ? alpha : bestValue;
		} else {
			bestValue = -bestValue;
			if (ab < bestValue) {
				bestValue = ab;
				*bestMove = possibleMoves[i];
			}
			beta = (beta < bestValue) ? beta : bestValue;
		}

		if (beta <= alpha) {
			break; // cut-off
		}

		delete boardClone;
	}

	this->transpositionTable[board->getBoard()] = bestValue;
	return bestValue;
}
