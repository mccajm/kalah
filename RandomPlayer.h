/*
 * RandomPlayer.h
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_
#include <vector>
#include "IPlayer.h"
#include "Board.h"
using namespace std;

class RandomPlayer: public IPlayer {
private:
	int n;
	Board *board;
	vector<int> getPossibleMoves();
public:
	RandomPlayer(int n);
	int getNextMove(Board *board);
};

#endif /* RANDOMPLAYER_H_ */
