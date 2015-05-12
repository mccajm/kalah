/*
 * RandomPlayer.h
 *
 *  Created on: 10 May 2015
 *      Author: adam
 */

#ifndef AIPlayer_H_
#define AIPlayer_H_
#include <vector>
#include <unordered_map>
#include "IPlayer.h"
#include "Board.h"
using namespace std;


typedef __uint128_t BoardInt;

struct TTEntry {
	unsigned int key;
	unsigned int value;
};

template <>
struct hash<BoardInt>
{
std::size_t operator()(const BoardInt& v) const
{
	// based on Hash128to64(const uint128& x) { in CityHash
	// http://cityhash.googlecode.com/svn-history/trunk/src/city.h
	// TODO: test with this: http://stackoverflow.com/a/19966387
	uint64_t low = v >> 64;
	uint64_t high = (v - low) >> 64;

	const uint64_t kMul = 0x9ddfea08eb382d69ULL; // 2^64/phi
	uint64_t a = (hash<uint64_t>()(low) ^ hash<uint64_t>()(high) ) * kMul;
	a ^= (a >> 47);
	uint64_t b = (hash<uint64_t>()(high)  ^ a) * kMul;
	b ^= (b >> 47);
	b *= kMul;
	return b;
}
};


class AIPlayer: public IPlayer {
private:
	int n;
	int counter;
	unordered_map<BoardInt, int> transpositionTable;
	Board *board;
	TTEntry *buildTTEntry(Board *b, int v);
	vector<int> getPossibleMoves(Board *b);
	int alphaBeta(Board *board, int depth, int alpha, int beta, int maximisingPlayer);
public:
	AIPlayer(int n, Board *board);
	int getNextMove();
};

#endif /* AIPLAYER_H_ */
