//============================================================================
// Name        : kalah.cpp
// Author      : Adam McCarthy
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <cstdint>
#include "Board.h"
#include "IPlayer.h"
#include "RandomPlayer.h"
#include "AIPlayer.h"
using namespace std;

int main() {
/*
https://chessprogramming.wikispaces.com/Shared+Hash+Table
getPossibleMoves - any house which contains a seed
http://homepages.cwi.nl/~paulk/theses/Carolus.pdf
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.186.5391&rep=rep1&type=pdf
http://cswww.essex.ac.uk/cig/2005/papers/p1018.pdf

transposition table
mtd(f)
iterative deepening

	*/

	Board b;
	IPlayer *players[2];
	players[0] = new AIPlayer(0, &b);
	players[1] = new AIPlayer(1, &b);
	int currentPlayer = rand() % 2;
	b.print();
	while ((b.getKalah(0) + b.getKalah(1)) < 60) {
		cout << b.getScore() << endl;
		int move = players[currentPlayer]->getNextMove();
		cout << "Player " << currentPlayer << " " << move << endl;
		if (move != -1) {
			b.sowFrom(move);
		}

		b.print();
		currentPlayer = !currentPlayer;
	}

	delete players[0];
	delete players[1];

	cout << "End" << endl;
	return 0;
}
