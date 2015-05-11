/*
 * AIPlayer.cpp
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#include <cstdlib>
#include <iostream>
#include "AIPlayer.h"

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
    double bestV = -numeric_limits<int>::max();
    vector<int> possibleMoves = this->getPossibleMoves(this->board);
    for (std::vector<int>::iterator it = possibleMoves.begin() ; it != possibleMoves.end(); ++it) {
    	Board *boardClone = board->clone();
    	boardClone->sowFrom(*it);
    	double v = this->alphaBeta(boardClone, 12, -numeric_limits<int>::max(), numeric_limits<int>::max(), 1);
    	if (v > bestV) {
    		nextMove = *it;
    	}
    	this->counter++;
    }

    cout << this->counter << " Nodes traversed" << endl;

    return nextMove;
}
//alphabeta(origin, depth, -inf, +inf, TRUE)
double AIPlayer::alphaBeta(Board *board, int depth, int alpha, int beta, int maximisingPlayer) {
	this->counter++;
	if (depth == 0 || (board->getKalah(0) + board->getKalah(1) == board->NUMBER_OF_SEEDS)) {
		return board->getScore();
	}

	int v = -numeric_limits<int>::max();
	vector<int> possibleMoves = this->getPossibleMoves(this->board);
	for (std::vector<int>::iterator it = possibleMoves.begin() ; it != possibleMoves.end(); ++it) {
		Board *boardClone = board->clone();
		boardClone->sowFrom(*it);
		double ab = this->alphaBeta(boardClone, depth-1, alpha, beta, !maximisingPlayer);
		if (maximisingPlayer) {
			if (ab > v) v = ab;
			alpha = (alpha > v) ? alpha : v;
		} else {
			v = -v;
			if (ab < v) v = ab;
			beta = (beta < v) ? beta : v;
		}

		if (beta <= alpha) {
			break; // b cut-off
		}
	}

	return v;
}
/*
function alphabeta(node, depth, a, b, maximizingPlayer)
02      if depth = 0 or node is a terminal node
03          return the heuristic value of node
04      if maximizingPlayer
05          v := -infinity
06          for each child of node
07              v := max(v, alphabeta(child, depth - 1, a, b, FALSE))
08              a := max(a, v)
09              if b <= a
10                  break (* b cut-off *)
11          return v
12      else
13          v := inf
14          for each child of node
15              v := min(v, alphabeta(child, depth - 1, a, b, TRUE))
16              b := min(b, v)
17              if b <= a
18                  break (* a cut-off *)
19          return v
*/
