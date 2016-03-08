#include "player.h"
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    
    board = new Board();
    playerSide = side;
    opponentSide = side == WHITE ? BLACK : WHITE;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // Process opponent move
    board->doMove(opponentsMove, opponentSide);
    // Compute all possible 2-ply moves
    std::vector<Move> playerMoves;
    std::vector< std::vector<Move> > opponentMoves;
    Board *experiment = board->copy();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move playerMove = Move(i, j);
            if (experiment->checkMove(&playerMove, playerSide)) {
                experiment->doMove(&playerMove, playerSide);
                playerMoves.push_back(playerMove);
                std::vector<Move> someMoves;
                for (int m = 0; m < 8; m++) {
                    for (int n = 0; n < 8; n++) {
                        Move opponentMove = Move(m, n);
                        if (experiment->checkMove(&opponentMove, opponentSide)) {
                            someMoves.push_back(opponentMove);
                        }
                    }
                }
                experiment = board->copy();
                opponentMoves.push_back(someMoves);
            }
        }
    }
    delete experiment;
    if (playerMoves.size() == 0) {
        return NULL;
    } else {
        // Assign each pair of moves a heuristic and determine the minimax
        Board *experiment = board->copy();
        int maximum;
        int index = 0;
        for (int i = 0; i < (int) playerMoves.size(); i++) {
            int minimum;
            if (opponentMoves[i].size() == 0) {
                minimum = 65;
            } else {
                for (int j = 0; j < (int) opponentMoves[i].size(); j++) {
                    experiment->doMove(&playerMoves[i], playerSide);
                    experiment->doMove(&opponentMoves[i][j], opponentSide);
                    int heuristic = experiment->count(playerSide) - experiment->count(opponentSide);
                    if (j == 0 || heuristic < minimum) {
                        minimum = heuristic;
                    }
                    experiment = board->copy();
                }
            }
            if (i == 0 || minimum > maximum) {
                maximum = minimum;
                index = i;
            }
        }
        delete experiment;
        // Make any move with max heuristic
        board->doMove(&playerMoves[index], playerSide);
        return new Move(playerMoves[index].getX(), playerMoves[index].getY());
    }
}

void Player::setBoard(char board[]) {
    this->board->setBoard(board);
}
