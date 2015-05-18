#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "Board.h"
#include "IPlayer.h"

class Game {
private:
	Board *board;
	IPlayer *players[2];

public:
	Game(Board *board, IPlayer *p1, IPlayer *p2);
	void mainLoop();
	virtual ~Game();
};

#endif /* SRC_GAME_H_ */
