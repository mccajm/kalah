/*
 * Game.cpp
 *
 *  Created on: 11 May 2015
 *      Author: adam
 */

#include <iostream>
#include "Game.h"
#include "IPlayer.h"
using namespace std;

Game::Game(Board *board, IPlayer *p1, IPlayer *p2) {
	this->board = board;
	this->players[0] = p1;
	this->players[1] = p2;
}

void Game::mainLoop() {
	int currentPlayer = rand() % 2;
	this->board->print();
	while ((this->board->getKalah(0) + this->board->getKalah(1)) < 60) {
		cout << this->board->getScore() << endl;
		int move = players[currentPlayer]->getNextMove();
		cout << "Player " << currentPlayer << " " << move << endl;
		if (move != -1) {
			this->board->sowFrom(move);
		}

		this->board->print();
		currentPlayer = !currentPlayer;
	}
}

Game::~Game() {
	delete this->players[0];
	delete this->players[1];
}

