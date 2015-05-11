/*
 * RandomPlayer.h
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#ifndef IPLAYER_H_
#define IPLAYER_H_

class IPlayer {
public:
	virtual int getNextMove() = 0;
	virtual ~IPlayer() {};
};

#endif /* IPLAYER_H_ */
