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
	vector<int> possibleMoves;
	void updatePossibleMoves();
public:
	RandomPlayer(int n, Board *board);
	virtual ~RandomPlayer();
	int getNextMove();
};

#endif /* RANDOMPLAYER_H_ */
