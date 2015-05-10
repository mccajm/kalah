/*
 * Board.h
 *
 *  Created on: 8 May 2015
 *      Author: adam
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <stdint.h>

class Board {
private:
	__int128_t houses;
	void sow(int src_house, int dst_house);
	int convertHouseToShift(int house);

public:
	int getHouse(int house);
	int getKalah(int player);
	double getScore();
	void sowFrom(int house);
	void print();
	Board();
};
#endif /* BOARD_H_ */
