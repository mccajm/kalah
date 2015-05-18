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

/* Create a shallow copy of the board.
 * Ensures that players can't modify the board.
 * Allows AI players to create clones in order to build game trees.
 */
Board *Board::clone() {
     return new Board(*this);
}

// 1 seed in house 1 = 1, 1 seed in house 2 = 1000000 etc
int Board::convertHouseToShift(int house) {
	return house * this->HOUSE_BIT_WIDTH;
}

// Sow a seed from src_house to dst_house
void Board::sow(int src_house, int dst_house) {
	BoardInt src = (src_house == -1) ? 0 : (BoardInt)1 << this->convertHouseToShift(src_house);
	BoardInt dst = (BoardInt)1 << this->convertHouseToShift(dst_house);

	this->board += -src + dst;
}

// Get the number of seeds in <player>'s kalah
int Board::getKalah(int player) {
	return this->getHouse(0 + player*this->SIDE_WIDTH);
}

// Get the number of seeds in <player>'s house number <house>
int Board::getHouse(int house) {
	int shift = this->convertHouseToShift(house);
	BoardInt bits = this->board & ((BoardInt)0b111111 << shift);
	return bits >> shift;
}


// Return the IDs of all <player>'s houses
vector<int> Board::getHouses(int player) {
	vector<int> houses;
	for (int i = 1; i < this->SIDE_WIDTH; i++) {
		houses.push_back(i + player*this->SIDE_WIDTH);
	}

	return houses;
}

// Sow all seeds anticlockwise from <house>
pair<int, bool> Board::sowFrom(int house) {
    int seeds = this->getHouse(house);
    int h = house;
    bool wasEmpty = false;
    for (int i = 1; i <= seeds; i++) {
    	if (--h < 0) { // 13 is anticlockwise from 0
    		h = 13;
    	}

    	this->sow(house, h);
    }

    // Record whether the last house was empty
	if (this->getHouse(h) == 0) {
		wasEmpty = true;
	}

	// Return the last house and whether it was empty
    return pair<int, bool>(h, wasEmpty);
}

// Sow all of the seeds in src_house to dst_house
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

// Score is just the difference between the number of seeds in Kalah 0 and 1.
int Board::getScore() {
	return this->getKalah(0) - this->getKalah(1);
}

// Returns the BoardInt representing the board
BoardInt Board::getBoard() {
	return this->board;
}

int Board::getOppositeHouse(int house) {
	return 14-house;
}


