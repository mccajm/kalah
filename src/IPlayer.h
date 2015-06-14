/*
 * IPlayer.h
 *
 *  Interface for a pluggable player
 */

#ifndef IPLAYER_H_
#define IPLAYER_H_
#include "Board.h"

const int NULL_MOVE = -1;

class IPlayer {
public:
	virtual int getNextMove(Board *board) = 0;
	virtual ~IPlayer() {};
};

#endif /* IPLAYER_H_ */
