/*
 * Kalah Game
 * Author: Adam McCarthy
 *
 * Plaat, A. (1999). MTD (f), A Minimax Algorithm faster than NegaScout.
 * Irving, G., Donkers, H. H. L. M., & Uiterwijk, J. W. H. M. (2000). Solving kalah. ICGA Journal, 23(3), 139-148.
 * Batenkov, D. (2006). Modern developments of Shannon's Chess. Faculty of mathematics and computer science.
 * Carolus, J. W. (2006). Alpha-beta with sibling prediction pruning in chess. Wiskunde en Informatica: Univ. of Amsterdam.
 * SHIBAHARA, K., INUI, N., & KOTANI, Y. Adaptive Strategies of MTD-f for Actual Games.
 *
 */

#include <iostream>
#include <ctime>
#include "Board.h"
#include "IPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Game.h"
using namespace std;

int main() {
	Board b;
	IPlayer *players[2];
    string playerType;

	cout << ":: Kalah Game" << endl << endl;

	srand(time(NULL));
    for (int i = 0; i < 2; i++) { // Query the user for the type of Player 1 and Player 2
		cout << ":: Player " << i+1 << ": Select type by entering Human, Random or AI: ";

		cin >> playerType;
		if (playerType == "Human") {
			players[i] = new HumanPlayer(i);
		} else if (playerType == "Random") {
			players[i] = new RandomPlayer(i);
		} else if (playerType == "AI") {
			players[i] = new AIPlayer(i);
		} else {
			cout << "Invalid Choice" << endl;
			return 1;
		}
    }

	Game game(&b, players[0], players[1]);
	game.mainLoop();

	return 0;
}
