/*
 * RandomPlayer.h
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_
#include <vector>
#include "IPlayer.h"
#include "Board.h"
using namespace std;

class HumanPlayer: public IPlayer {
private:
	int n;
	Board *board;
	vector<int> possibleMoves;
	void updatePossibleMoves();
	vector<int>::iterator getMoveAsInput();
public:
	HumanPlayer(int n, Board *board);
	int getNextMove();
};

#endif /* HUMANPLAYER_H_ */
