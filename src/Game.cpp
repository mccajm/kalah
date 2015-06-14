/*
 * Game.cpp
 *
 *  Game mainloop
 */

#include <iostream>
#include <algorithm>
#include "Game.h"
#include "IPlayer.h"
using namespace std;

Game::Game(Board *board, IPlayer *p1, IPlayer *p2) {
	this->board = board;
	this->players[0] = p1;
	this->players[1] = p2;
}

void Game::mainLoop() {
	int currentPlayer = 0;
	int totalMoves = 0;
	this->board->print();
	// Loop until all of the seeds are in the Kalahs
	while ((this->board->getKalah(0) + this->board->getKalah(1)) < this->board->NUMBER_OF_SEEDS) {
		// Pass a clone of the board to the player so an attacker can't cheat
		int move = players[currentPlayer]->getNextMove(this->board->clone());
		if (move != NULL_MOVE) {
			cout << ":: Player " << currentPlayer+1 << " sowing from " << move << endl;
			pair<int, bool> lastHouse = this->board->sowFrom(move); // Sow seeds anticlockwise
			vector<int> houses = this->board->getHouses(currentPlayer);
			if (find(houses.begin(), houses.end(), lastHouse.first) != houses.end()) {
				/* Rule 5 from Wikipedia:
				 *  If the last sown seed lands in an empty house owned by the player, and
				 *  the opposite house contains seeds, both the last seed and the opposite
				 *  seeds are captured and placed into the player's store.
				 */
				if (lastHouse.second) {
					int opHouse = this->board->getOppositeHouse(lastHouse.first);
					int opSeeds = this->board->getHouse(opHouse);
					if (opSeeds > 0) {
						this->board->sowAll(lastHouse.first, 0 + currentPlayer*this->board->SIDE_WIDTH);
						this->board->sowAll(opHouse, 0 + currentPlayer*this->board->SIDE_WIDTH);
						cout << ":: Last seed landed in an empty house and the opposite house" << endl;
						cout << ":: isn't empty so both moved into " << currentPlayer+1 << "'s kalah" << endl;
					}
				}

				/* Rule 4 from Wikipedia:
				 *  If the last sown seed lands in the player's store, the player gets
				 *  an additional move. There is no limit on the number of moves a player
				 *  can make in their turn.
				 */
				cout << ":: Last seed landed in Player " << currentPlayer+1 << "'s house so they get another move" << endl;
				currentPlayer = !currentPlayer;
			}
		} else { // NULL_MOVE
            cout << ":: Player " << currentPlayer+1 << " can't make a move" << endl << endl;
            /* Rule 6 from Wikipedia:
             *  When one player no longer has any seeds in any of their
             *  houses, the game ends. The other player moves all remaining seeds to their store,
             *  and the player with the most seeds in their store wins. */
        	for (int player = 0; player < 2; player++) {
        	    vector<int> houses = this->board->getHouses(player);
        	    for (int i = 0; i < (int)houses.size(); i++) {
                    this->board->sowAll(houses.at(i), 0 + player*this->board->SIDE_WIDTH);
        	    }
        	}
		}

		cout << endl;
		this->board->print();
		currentPlayer = !currentPlayer;
		totalMoves++;
	}

	int score = this->board->getScore();
	if (score > 0) {
		cout << ":: Player 1 won";
	} else if (score < 0) {
		cout << ":: Player 2 won";
	} else {
		cout << ":: Draw";
	}

	cout << " in " << totalMoves << " moves" << endl;
}

Game::~Game() {
	delete this->players[0];
	delete this->players[1];
}

