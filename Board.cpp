/*
 * Board.cpp
 *
 *  Created on: 8 May 2015
 *      Author: adam
 */

#include <iostream>
#include "Board.h"
using namespace std;


Board::Board(void) {
    this->houses = 0;
	this->NUMBER_OF_SEEDS = 30;
	for (int i=0; i < this->NUMBER_OF_SEEDS; i++) {
		this->sow(-1, rand() % 6);
		this->sow(-1, (rand() % 6) + 7);
	}
	cout << "Board created" << endl;
}

Board *Board::clone() const {
     return new Board(*this);
}

// Make this fit NUMBER_OF_SEEDS*2
int Board::convertHouseToShift(int house) {
	int shift = house * 5;
	if (house > 6) { // Kalahs are 6 bits
		shift++;
	}

	return shift;
}

void Board::sow(int src_house, int dst_house) {
	BoardInt src = (src_house == -1) ? 0 : (BoardInt)1 << this->convertHouseToShift(src_house);
	BoardInt dst = (BoardInt)1 << this->convertHouseToShift(dst_house);

	this->houses += -src + dst;
}

int Board::getKalah(int player) {
	return this->getHouse(6 + player*7);
}

int Board::getHouse(int house) {
	int shift = this->convertHouseToShift(house);
	int val = 0;
	int len = 5;
	if (house == 6 || house == 13) {
		len++;
	}
	for (int i = 0; i < len; i++) {
		int bit = (this->houses >> (shift+i)) & 1;
		val += bit * (1 << i);
	}

	return val;
}

void Board::sowFrom(int house) {
    int seeds = this->getHouse(house);
    int h = house;
    for (int i = 1; i <= seeds; i++) {
    	if (--h < 0) {
    		h = 13;
    	}

    	this->sow(house, h);
    }
}

void Board::print() {
	cout << "Player 2" << "\t\t\t\t\t\t" << "Player 1" << endl;
	for (int i = 0; i <=5; i++) {
		cout << "\t" << i << ":" << this->getHouse(i);
	}
	cout << endl;

	cout << this->getKalah(1) << "\t\t\t\t\t\t\t" << this->getKalah(0) << endl;
	for (int i = 12; i > 6; i--) {
		cout << "\t" << i << ":" << this->getHouse(i);
	}

	cout << endl << endl;
}

int Board::getScore() {
	return this->getKalah(0) - this->getKalah(1);
}

BoardInt Board::getBoard() {
	return this->houses;
}
