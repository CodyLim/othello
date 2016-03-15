#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    void setBoard(char board[64]);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Board *board;
    Side playerSide;
    Side opponentSide;
    int heuristic_score[8][8] = {
			{10, -3, 4, 4, 4, 4, -3, 10},
			{-3, -5, 2, 2, 2, 2, -5, -3},
			{4, 2, 2, 2, 2, 2, 2, 4},
			{4, 2, 2, 2, 2, 2, 2, 4},
			{4, 2, 2, 2, 2, 2, 2, 4},
			{4, 2, 2, 2, 2, 2, 2, 4},
			{-3, -5, 2, 2, 2, 2, -5, -3},
			{10, -3, 4, 4, 4, 4, -3, 10},
	};
	int pvs(Board game_board, Side player_Side, Side opponent_Side, \
	int alpha, int beta, int depth);
};

#endif
