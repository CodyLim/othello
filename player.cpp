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
Player::~Player() 
{
    delete board;
}

/*Principal variation search (PVS) based on Wikipedia pseudocode.
 */
int Player::pvs(Board game_board, Side player_Side, Side opponent_Side, \
int alpha, int beta, int depth)
{
	if (depth <= 0 || game_board.hasMoves(player_Side) == false)
	{
		int score = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if(game_board.get(player_Side, j, i))
				{
					score += heuristic_score[j][i];
				}
				else if (game_board.get(opponent_Side, j, i))
				{
					score -= heuristic_score[j][i];
				}
			}
		}
		return score;
	}
	else
	{
		// Compute all possible 2-ply moves for the player's side
		std::vector<Move*> playerMoves;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Move * playerMove = new Move(j, i);
				if (game_board.checkMove(playerMove, player_Side))
				{
					playerMoves.push_back(playerMove);
				}
			}
		}
		for (unsigned int i = 0; i < playerMoves.size(); i++)
		{
			Board *experiment = game_board.copy();
			experiment->set(player_Side, playerMoves.at(i)->getX(), \
			playerMoves.at(i)->getY());
			int score;
			if (i != 0)
			{
				score = -pvs(*experiment, opponent_Side, player_Side, \
				-alpha - 1, -alpha, depth - 1);
				if (alpha < score && score < beta)
				{
					score = -pvs(*experiment, opponent_Side, player_Side, \
					-beta, -score, depth - 1);
				}
			}
			else
			{
				score = -pvs(*experiment, opponent_Side, player_Side, \
				-beta, -alpha, depth - 1);
			}
			alpha = max(alpha, score);
			if (alpha >= beta)
			{
				return alpha;
			}
		}
		return alpha;
	}
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
    if (opponentsMove != NULL)
    {
		board->doMove(opponentsMove, opponentSide);
	}
	// Compute all possible 2-ply moves for the player's side
    std::vector<Move*> playerMoves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * playerMove = new Move(j, i);
            if ((*board).checkMove(playerMove, playerSide))
            {
                playerMoves.push_back(playerMove);
            }
        }
    }
    if (playerMoves.size() == 0) 
    {
        return NULL;
    }
    else
    {
		int high_score = -999999;
		Move * optimal_move = playerMoves.at(0);
		for (unsigned int i = 0; i < playerMoves.size(); i++)
		{
			Board *experiment = board->copy();
			experiment->set(playerSide, playerMoves.at(i)->getX(), \
			playerMoves.at(i)->getY());
			int score = -pvs(*experiment, opponentSide, playerSide, \
			-9001, 9001, 3);
			if (high_score < score)
			{
				high_score = score;
				optimal_move = playerMoves.at(i);
			}
		}
		board->doMove(optimal_move, playerSide);
		return optimal_move;
	}
}
		

void Player::setBoard(char board[]) {
    this->board->setBoard(board);
}
