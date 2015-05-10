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
	const int NUMBER_OF_SEEDS = 30;
	for (int i=0; i < NUMBER_OF_SEEDS; i++) {
		this->sow(-1, rand() % 6);
		this->sow(-1, (rand() % 6) + 7);
	}
	cout << "Board created" << endl;
}

int Board::convertHouseToShift(int house) {
	int shift = house * 5;
	if (house > 6) { // Kalahs are 6 bits
		shift++;
	}

	return shift;
}

void Board::sow(int src_house, int dst_house) {
	__uint128_t src = (src_house == -1) ? 0 : (__uint128_t)1 << this->convertHouseToShift(src_house);
	__uint128_t dst = (__uint128_t)1 << this->convertHouseToShift(dst_house);

	if (dst_house == 13) {
		int a = 0;
	}

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
	cout << ": Sowing from " << house << endl;
    int seeds = this->getHouse(house);
    int h = house;
    for (int i = 1; i <= seeds; i++) {
    	if (--h < 0) {
    		h = 13;
    	}

    	this->sow(house, h);
        cout << ": Sowing " << seeds << " into " << h;
    }

    cout << endl;
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

double Board::getScore() {
	double total = getKalah(0) + getKalah(1);
	if (total == 0) {
		return 0;
	}

	return (this->getKalah(0)-this->getKalah(1))/total;
}
/*
int Board::getWinner() {
	int *kalahs = new int[2];
	for (int i = 0; i < 2; i++)
		kalahs[i] = this->getKalah(i);

	if (kalahs[0] > 30)
		return 0;
	else if (kalahs[1] > 30)
		return 1;
	else if ((kalahs[0] + kalahs[1]) == 60)
		return 2;

	return -1;
}
*/
