/*
 * Board.h
 *
 *  Created on: 8 May 2015
 *      Author: adam
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <stdint.h>

typedef __uint128_t BoardInt;

class Board {
private:
	BoardInt houses;
	void sow(int src_house, int dst_house);
	int convertHouseToShift(int house);

public:
	int NUMBER_OF_SEEDS;
	int getHouse(int house);
	int getKalah(int player);
	int getScore();
	void sowFrom(int house);
	void print();
	BoardInt getBoard();
	Board();
	virtual Board *clone() const;
	virtual ~Board() {};
};
#endif /* BOARD_H_ */
