/*
 * RandomPlayer.h
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#ifndef AIPlayer_H_
#define AIPlayer_H_
#include <vector>
#include "IPlayer.h"
#include "Board.h"
using namespace std;

class AIPlayer: public IPlayer {
private:
	int n;
	int counter;
	Board *board;
	vector<int> getPossibleMoves(Board *b);
	double alphaBeta(Board *board, int depth, int alpha, int beta, int maximisingPlayer);
public:
	AIPlayer(int n, Board *board);
	int getNextMove();
};

#endif /* AIPLAYER_H_ */
