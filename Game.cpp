/*
 * Game.cpp
 *
 *  Created on: 11 May 2015
 *      Author: adam
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
	// Check for permitted moves!
	int currentPlayer = 0;
	this->board->print();
	int c = 0;
	while ((this->board->getKalah(0) + this->board->getKalah(1)) < this->board->NUMBER_OF_SEEDS) {
		int move = players[currentPlayer]->getNextMove();
		if (move != -1) {
			cout << ":: Player " << currentPlayer+1 << " sowing from " << move << endl;
			pair<int, bool> lastHouse = this->board->sowFrom(move);
			vector<int> houses = this->board->getHouses(currentPlayer);
			if (find(houses.begin(), houses.end(), lastHouse.first) != houses.end()) {
				cout << ":: Last seed landed in Player " << currentPlayer+1 << "'s house so they get another move" << endl;

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

				currentPlayer = !currentPlayer;
			}
		} else {
            cout << ":: Player " << currentPlayer+1 << " can't make a move" << endl << endl;
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
		c++;
	}

	int score = this->board->getScore();
	if (score > 0) {
		cout << ":: Player 1 won";
	} else if (score < 0) {
		cout << ":: Player 2 won";
	} else {
		cout << ":: Draw";
	}

	cout << " in " << c << " moves" << endl;
}

Game::~Game() {
	delete this->players[0];
	delete this->players[1];
}

