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
	return house * 6;
}

void Board::sow(int src_house, int dst_house) {
	BoardInt src = (src_house == -1) ? 0 : (BoardInt)1 << this->convertHouseToShift(src_house);
	BoardInt dst = (BoardInt)1 << this->convertHouseToShift(dst_house);

	this->board += -src + dst;
}

int Board::getKalah(int player) {
	return this->getHouse(0 + player*7);
}

int Board::getHouse(int house) {
	int shift = this->convertHouseToShift(house);
	int val = 0;
	for (int i = 0; i < 6; i++) {
		int bit = (this->board >> (shift+i)) & 1;
		val += bit * (1 << i);
	}

	return val;
}


vector<int> Board::getHouses(int player) {
	vector<int> houses;
	for (int i = 1; i < 7; i++) {
		houses.push_back(i + player*7);
	}

	return houses;
}

int Board::sowFrom(int house) {
    int seeds = this->getHouse(house);
    int h = house;
    for (int i = 1; i <= seeds; i++) {
    	if (--h < 0) {
    		h = 13;
    	}

    	this->sow(house, h);
    }

    return h;
}

void Board::print() {
	cout << "Player 1" << "\t\t\t\t\t\t" << "Player 2" << endl;
	vector<int> p1Houses = this->getHouses(0);
	for (int i = 0; i < (int)p1Houses.size(); i++) {
		cout << "\t" << i+1 << ":" << this->getHouse(p1Houses[i]);
	}
	cout << endl;

	cout << this->getKalah(0) << "\t\t\t\t\t\t\t" << this->getKalah(1) << endl;

	vector<int> p2Houses = this->getHouses(1);
	for (int i = 0; i < (int)p2Houses.size(); i++) {
		cout << "\t" << i+1 << ":" << this->getHouse(p2Houses[i]);
	}

	cout << endl << endl;
}

int Board::getScore() {
	return this->getKalah(0) - this->getKalah(1);
}

BoardInt Board::getBoard() {
	return this->board;
}

void Board::endGame() {
	for (int player = 0; player < 2; player++) {
	    vector<int> houses = this->getHouses(player);
	    for (int i = 0; i < (int)houses.size(); i++) {
            while (this->getHouse(houses.at(i)) > 0) {
		        this->sow(houses.at(i), 0);
            }
	    }
	}
}
