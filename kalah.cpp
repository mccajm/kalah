//============================================================================
// Name        : kalah.cpp
// Author      : Adam McCarthy
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Board.h"
#include "IPlayer.h"
#include "RandomPlayer.h"
#include "AIPlayer.h"

#include "Game.h"
using namespace std;

int main() {
	Board b;
	Game game(&b, new AIPlayer(0, &b), new RandomPlayer(1, &b));
	game.mainLoop();

	cout << "End" << endl;
	return 0;
}
