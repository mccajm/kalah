Kalah Game
==========

Usage: ./kalah

Kalah(m, n), where m = holes per side and n = seeds per hole, has been strongly
solved up to Kalah(4,3) in the literature[1].  The problem defined here is,
effectively, Kalah(6, 30) due to the random allocation of seeds which results in
a state space which is far too large for which to compute a full-game database.
I therefore chose to use a minimax search algorithm, and selected MTD(f)[2] with
Iterative Deepening [2, 3, 4, 5] and a transposition table[3,4,5].

I used a bit representation for the board.  Each house could contain upto 60
seeds so I use 6 bits (2^6-1=63) to represent each house.  There are 14 houses
(*6 = 84bits), so I used a 128bit unsigned integer (__uint128_t in gcc).  I
chose this representation because it means sowing can be simply represented by
addition and subtraction and I no longer need to use a hash function to
represent the board in the game tree.  It also reduces the memory usage of the
board from 14*sizeof(int) (generally 448bits) to 128bits.

Players are represented with an interface - IPlayer - which allows pluggable
players to be added.  AIPlayer, RandomPlayer and HumanPlayer are currently
included.

Further work would be to parallelise the search algorithm, but I have not done
this due to limited time. A major omission is unit testing, which I would add
given further time.

1. Irving, G., Donkers, H. H. L. M., & Uiterwijk, J. W. H. M. (2000). Solving
kalah. ICGA Journal, 23(3), 139-148.
2. Plaat, A. (1999). MTD (f), A Minimax Algorithm faster than NegaScout.
3. Batenkov, D. (2006). Modern developments of Shannon's Chess. Faculty of
mathematics and computer science.
4. SHIBAHARA, K.,INUI, N., & KOTANI, Y. Adaptive Strategies of MTD-f for Actual
Games.
5. Carolus, J. W. (2006). Alpha-beta with sibling prediction pruning in chess.
Wiskunde en Informatica: Univ. of Amsterdam.
