/*
 * IPlayer which constructs a minimax tree and uses
 *  MTD(f) and a transposition table to search for
 *  optimal moves.
 */

#include <cstdlib>
#include <limits>
#include <ctime>
#include "AIPlayer.h"

AIPlayer::AIPlayer(int n) {
	this->n = n;
	// ~7MB preallocated to prevent repetitive malloc()
	this->transpositionTable.reserve(409600);
}

// Move this into board
vector<int> AIPlayer::getPossibleMoves(Board *board) {
	vector<int> possibleMoves;
	for (int i = 1; i < board->SIDE_WIDTH; i++) {
		if (board->getHouse(i + this->n*board->SIDE_WIDTH) > 0) {
			possibleMoves.push_back(i + this->n*board->SIDE_WIDTH);
		}
	}

	return possibleMoves;
}

int AIPlayer::getNextMove(Board *board) {
    if (this->getPossibleMoves(board).size() == 0) {
        return NULL_MOVE;
    }

    // Iterative Deepening
    int bestMove = NULL_MOVE;
    clock_t start = clock();
    for (int depth = 0; depth < 1000; depth++) {  // Average game length ~= 100 so try upto 1000 depth
        bestMove = mtdf(board, this->getPossibleMoves(board).at(0), depth);
        // If traversal has taken longer than 2 seconds, return the best move so far
        if ((clock() - start) / (double) CLOCKS_PER_SEC > 2) {
        	break;
        }
    }

    // Move selected, clear the transpositonTable
    this->transpositionTable.clear();
    return bestMove;
}

int AIPlayer::mtdf(Board *board, int f, int depth) {
	/*
	 * Plaat, A. (1999). MTD (f), A Minimax Algorithm faster than NegaScout.
	 * http://people.csail.mit.edu/plaat/mtdf.html
	 */
	int bestMove = f;
	int upperBound = numeric_limits<int>::max();
	int lowerBound = -numeric_limits<int>::max();
	while (lowerBound < upperBound) {
	    int beta = f;
	    if (f == lowerBound) {
	    	beta++;
	    }

	    f = this->alphaBeta(board, depth, beta-1, beta, this->n, &bestMove);
	    if (f < beta) {
	    	upperBound = f;
	    } else {
	    	lowerBound = f;
	    }
	}

	return bestMove;
}

int AIPlayer::alphaBeta(Board *board, int depth, int alpha, int beta, int player, int *bestMove) {
	/*
	 * Plaat, A. (1999). MTD (f), A Minimax Algorithm faster than NegaScout.
	 * http://people.csail.mit.edu/plaat/mtdf.html
	 */
	// Has the value been previously computed?
	if (this->transpositionTable.count(board->getBoard()) > 0) {
        /* If this was parallelised I would implement a lockless transposition table
		 * https://cis.uab.edu/hyatt/hashing.html
		 * or use a spinlock */
		return this->transpositionTable.at(board->getBoard());
	}

	// Rule 6
	vector<int> possibleMoves = this->getPossibleMoves(board);
	if ((int)this->getPossibleMoves(board).size() == 0) {
		for (int p = 0; p < 2; p++) {
			vector<int> houses = board->getHouses(p);
			for (int i = 0; i < (int)houses.size(); i++) {
				board->sowAll(houses.at(i), 0 + p*board->SIDE_WIDTH);
			}
		}

	    return board->getScore();
	}

	// Reached final depth or the game is in an endstate, so return the score
	if (depth == 0 || (board->getKalah(0) + board->getKalah(1) == board->NUMBER_OF_SEEDS)) {
		return board->getScore();
	}

	int bestValue = -numeric_limits<int>::max();
	// Try each possible move at this level in the tree
	for (int checkMove = 0; checkMove < (int)possibleMoves.size(); checkMove++) {
		if (player == 1) {
			bestValue = numeric_limits<int>::max();
		}

		Board *boardClone = board->clone();
		pair<int, bool> lastHouse = boardClone->sowFrom(possibleMoves[checkMove]);
		vector<int> houses = boardClone->getHouses(player);
		if (find(houses.begin(), houses.end(), lastHouse.first) != houses.end()) {
			// Rule 5
			if (lastHouse.second) {
				int opHouse = boardClone->getOppositeHouse(lastHouse.first);
				int opSeeds = boardClone->getHouse(opHouse);
				if (opSeeds > 0) {
					boardClone->sowAll(lastHouse.first, 0 + player*board->SIDE_WIDTH);
					boardClone->sowAll(opHouse, 0 + player*board->SIDE_WIDTH);
				}
			}

			// Rule 4
			player = !player;
		}

		int ab = this->alphaBeta(boardClone, depth-1, alpha, beta, !player, NULL);
		if (player == 0) { // maximising player
			if (ab > bestValue) {
				bestValue = ab;
				if (bestMove) {
					*bestMove = possibleMoves[checkMove];
				}
			}

			if (bestValue > alpha) alpha = bestValue;
			if (bestValue < beta) {
				delete boardClone;
				break;
			}
		} else { // minimising player
			if (ab < bestValue) {
				bestValue = ab;
				if (bestMove) {
					*bestMove = possibleMoves[checkMove];
				}
			}

			if (bestValue < beta) beta = bestValue;
			if (bestValue > alpha) {
				delete boardClone;
				break;
			}
		}

		delete boardClone;
	}

	// Record the score for this board in the transposition table
	this->transpositionTable[board->getBoard()] = bestValue;
	return bestValue;
}
