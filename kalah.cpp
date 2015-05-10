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
using namespace std;

int main() {
	/*
	 * 30 seeds (5 bits == 32) * 12 houses = 60 bits #==> uint64_t
	def sow(board, i):
	...     sub = 1
	...     if i > 0:
	...         sub = 2 << (i*5-1)
	...     return board - sub + (2 << ((i+1)*5-1))

	typedef std::bitset<sizeof(uint64_t)> UINT65Bits;
	UINT65Bits b = UINT65Bits(board)
	int seeds = 0;
	for (int j = 0; j < 5; j++) {
		seeds = b.test(i*5+j-1);
http://www.boost.org/doc/libs/1_36_0/libs/graph/example/family-tree-eg.cpp
http://www.boost.org/doc/libs/1_51_0/libs/graph/doc/adjacency_list.html
root node is 0

getPossibleMoves - any house which contains a seed
http://homepages.cwi.nl/~paulk/theses/Carolus.pdf
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.186.5391&rep=rep1&type=pdf
http://cswww.essex.ac.uk/cig/2005/papers/p1018.pdf

alphabeta(origin, depth, -inf, +inf, TRUE)

function alphabeta(node, depth, a, b, maximizingPlayer)
02      if depth = 0 or node is a terminal node
03          return the heuristic value of node
04      if maximizingPlayer
05          v := -infinity
06          for each child of node
07              v := max(v, alphabeta(child, depth - 1, a, b, FALSE))
08              a := max(a, v)
09              if b <= a
10                  break (* b cut-off *)
11          return v
12      else
13          v := inf
14          for each child of node
15              v := min(v, alphabeta(child, depth - 1, a, b, TRUE))
16              b := min(b, v)
17              if b <= a
18                  break (* a cut-off *)
19          return v

transposition table
mtd(f)
iterative deepening

	*/

	Board b;
	IPlayer *players[2];
	players[0] = new RandomPlayer(0, &b);
	players[1] = new RandomPlayer(1, &b);
	int currentPlayer = rand() % 2;
	b.print();
	while ((b.getKalah(0) + b.getKalah(1)) < 60) {
		cout << b.getScore() << endl;
		int move = players[currentPlayer]->getNextMove();
		if (move != -1) {
			b.sowFrom(move);
		}

		b.print();
		currentPlayer = !currentPlayer;
	}

	cout << "End" << endl;
	return 0;
}
