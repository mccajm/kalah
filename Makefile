CC=/usr/local/Cellar/gcc/4.9.1/bin/g++-4.9
CFLAGS=-std=c++0x -O3 -Wall -c

kalah:
	$(CC) $(CFLAGS) -MMD -MP -MF"./src/AIPlayer.d" -MT"./src/AIPlayer.d" -o "./src/AIPlayer.o" "./src/AIPlayer.cpp"
	$(CC) $(CFLAGS) -MMD -MP -MF"./src/Board.d" -MT"./src/Board.d" -o "./src/Board.o" "./src/Board.cpp"
	$(CC) $(CFLAGS) -MMD -MP -MF"./src/Game.d" -MT"./src/Game.d" -o "./src/Game.o" "./src/Game.cpp"
	$(CC) $(CFLAGS) -MMD -MP -MF"./src/HumanPlayer.d" -MT"./src/HumanPlayer.d" -o "./src/HumanPlayer.o" "./src/HumanPlayer.cpp"
	$(CC) $(CFLAGS) -MMD -MP -MF"./src/RandomPlayer.d" -MT"./src/RandomPlayer.d" -o "./src/RandomPlayer.o" "./src/RandomPlayer.cpp"
	$(CC) $(CFLAGS) -MMD -MP -MF"./src/kalah.d" -MT"./src/kalah.d" -o "./src/kalah.o" "./src/kalah.cpp"
	$(CC) -o "./bin/kalah" ./src/AIPlayer.o ./src/Board.o ./src/Game.o ./src/HumanPlayer.o ./src/RandomPlayer.o ./src/kalah.o
	rm src/*.d src/*.o
