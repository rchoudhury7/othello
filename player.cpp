#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    color = side;
    if(color == WHITE)
    	oppColor = BLACK;
    else
    	oppColor = WHITE;
    playBoard = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete playBoard;
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

void Player::setBoard(char data[])
{
	playBoard->setBoard(data);
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
    playBoard->doMove(opponentsMove,oppColor);

    int depth = 3;
	std::vector<Move*> moves = playBoard->getMoves(color);
	std::vector<int> scores;
	int max_score = -900000;
	int scoreInd = 0;

	for(unsigned int i = 0; i < moves.size(); i++)
	{
		Board *board2 = playBoard->copy();
		board2->doMove(moves[i],color);
		int score = minimax(depth, oppColor, board2);
		if(score > max_score)
		{
			scoreInd = i;
			max_score = score;
		}
		delete board2;
	}
	if(moves.empty())
		return NULL;

	playBoard->doMove(moves[scoreInd], color);
	return moves[scoreInd];

}

int Player::minimax(int depth, Side side, Board *board)
{
	std::vector<Move*> moves = board->getMoves(side);
	
	if(depth == 0 || moves.empty())
	    return getScore(board, side);
	
	int max_score = -90000;
	int min_score = 90000;
	int alpha = -90000;
	int beta = 90000;
	if(side == color)
	{
		for(unsigned int i = 0; i < moves.size(); i++)
		{
			Board *board2 = board->copy();
			board2->doMove(moves[i], side);
			int score = minimax(depth - 1, oppColor, board2);
			if(alpha > score)
				alpha = score;
			if(score > max_score) 
			    max_score = score;
			if(alpha > beta)
				break;

			delete board2;
			
		}
		return max_score;
	}
	else 
	{
		for(unsigned int i = 0; i < moves.size(); i++)
		{
			Board *board2 = board->copy();
			board2->doMove(moves[i], side);
			      
			int score = minimax(depth - 1, color, board2);

			if(beta < score)
				beta = score;
			if(score < min_score) 
			{
			    min_score = score;
			}
			if(alpha > beta)
				break;


			delete board2;

		}
		return min_score;
	}
}


/**
 * @brief Heuristic function for scoring a move.
 *
 * @param side What side the player is on.
 * @param *board Pointer to a board with the move acted upon it.
 * @param *move The move that will be scored.
 *
 *@return score the heuristic score of the move
 */
 
int Player::getScore(Board *board, Side side)
{
    int score = 0;
    if (side == BLACK) 
    {
        score += 10 * (board->countBlack() - board->countWhite()); // number of pieces
		score +=  4 * (board->getMoves(BLACK).size() - board->getMoves(WHITE).size()); // number of moves
		score += 20 * (board->corners(BLACK) - board->corners(WHITE)); // number of corners
		score += 12 * (board->edges(BLACK) - board->edges(WHITE));
    }
    else 
    {
        score = 10 * (board->countWhite() - board->countBlack());
		score += 4 * (board->getMoves(WHITE).size() - board->getMoves(BLACK).size());
		score += 20 * (board->corners(WHITE) - board->corners(BLACK));
		score +=12 * (board->edges(BLACK) - board->edges(WHITE));
    }
	return score;
}

