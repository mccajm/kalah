/*
 * Board.h
 *
 *  Created on: 8 May 2015
 *      Author: adam
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <stdint.h>
#include <vector>
using namespace std;

typedef __uint128_t BoardInt;

class Board {
private:
	BoardInt board;
	void sow(int src_house, int dst_house);
	int convertHouseToShift(int house);
	const int HOUSE_BIT_WIDTH = 6;

public:
	const int NUMBER_OF_SEEDS = 60;
	const int SIDE_WIDTH = 7; // 6 houses + 1 kalah
	void sowAll(int src_house, int dst_house);
	int getHouse(int house);
	int getKalah(int player);
	int getScore();
	int getOppositeHouse(int house);
	vector<int> getHouses(int player);
	pair<int, bool> sowFrom(int house);
	void print();
	void endGame();
	BoardInt getBoard();
	Board();
	virtual Board *clone() const;
	virtual ~Board() {};
};
#endif /* BOARD_H_ */
