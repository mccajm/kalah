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
    this->board = 0;
	for (int i=0; i < this->NUMBER_OF_SEEDS/2; i++) {
		this->sow(-1, 1 + rand() % 6);
		this->sow(-1, 1 + (rand() % 6) + this->SIDE_WIDTH);
	}
}

Board *Board::clone() const {
     return new Board(*this);
}

int Board::convertHouseToShift(int house) {
	return house * this->HOUSE_BIT_WIDTH;
}

void Board::sow(int src_house, int dst_house) {
	BoardInt src = (src_house == -1) ? 0 : (BoardInt)1 << this->convertHouseToShift(src_house);
	BoardInt dst = (BoardInt)1 << this->convertHouseToShift(dst_house);

	this->board += -src + dst;
}

int Board::getKalah(int player) {
	return this->getHouse(0 + player*this->SIDE_WIDTH);
}

int Board::getHouse(int house) {
	int shift = this->convertHouseToShift(house);
	BoardInt bits = this->board & ((BoardInt)0b111111 << shift);
	return bits >> shift;
}


vector<int> Board::getHouses(int player) {
	vector<int> houses;
	for (int i = 1; i < this->SIDE_WIDTH; i++) {
		houses.push_back(i + player*this->SIDE_WIDTH);
	}

	return houses;
}

pair<int, bool> Board::sowFrom(int house) {
    int seeds = this->getHouse(house);
    int h = house;
    bool wasEmpty = false;
    for (int i = 1; i <= seeds; i++) {
    	if (--h < 0) {
    		h = 13;
    	}

    	this->sow(house, h);
    }

	if (this->getHouse(h) == 0) {
		wasEmpty = true;
	}

    return pair<int, bool>(h, wasEmpty);
}

void Board::sowAll(int src_house, int dst_house) {
	while (this->getHouse(src_house) > 0) {
		this->sow(src_house, dst_house);
	}
}

void Board::print() {
	cout << "1" << "\t\t\t\t\t\t\t" << "2" << endl;
	cout << "-" << "\t\t\t\t\t\t\t" << "-" << endl;
	vector<int> p1Houses = this->getHouses(0);
	for (int i = 0; i < (int)p1Houses.size(); i++) {
		cout << "\t" << p1Houses[i] << ":" << this->getHouse(p1Houses[i]);
	}
	cout << endl;

	cout << this->getKalah(0) << "\t\t\t\t\t\t\t" << this->getKalah(1) << endl;

	vector<int> p2Houses = this->getHouses(1);
	for (int i = (int)p2Houses.size()-1; i >= 0; i--) {
		cout << "\t" << p2Houses[i] << ":" << this->getHouse(p2Houses[i]);
	}

	cout << endl << endl;
}

int Board::getScore() {
	return this->getKalah(0) - this->getKalah(1);
}

BoardInt Board::getBoard() {
	return this->board;
}

int Board::getOppositeHouse(int house) {
	return 14-house;
}


