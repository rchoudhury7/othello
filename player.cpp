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
		//stderr << "yoyoyoyoy" << endl;
		Board *board2 = playBoard->copy();
		board2->doMove(moves[i],color);
		int score = minimax(depth, oppColor, board2);
		if(score > max_score)
		{
			scoreInd = i;
			max_score = score;
		}
	}
	if(moves.empty())
		return NULL;

	playBoard->doMove(moves[scoreInd], color);
	return moves[scoreInd];

}

int Player::minimax(int depth, Side side, Board *board)
{
	std::vector<Move*> moves = board->getMoves(side);
	Side oSide = WHITE;
	if(side == WHITE)
		oSide = BLACK;

	if(depth == 1 || moves.empty())
		return getBestGreedyMove(board, side);

	int max_score = -900000;
	int min_score = 900000;
	for(unsigned int i = 0; i < moves.size(); i++)
	{
		Board *board2 = board->copy();
		board2->doMove(moves[i], side);
		int score = minimax(depth - 1, oSide, board2);
		if(score > max_score)
			max_score = score;
		if(score < min_score)
			min_score = score;
	}
	if(side == color)
		return max_score;
	return min_score;
}

// this will get the best move for a side given the board.
int Player::getBestGreedyMove(Board *board, Side side)
{
	std::vector<int> scores;
    std::vector<Move*> moves = board->getMoves(side);

    for(unsigned int i = 0; i < moves.size(); i++) // simple heuristic
    {
    	Board *copy = board->copy();
    	copy->doMove(moves[i],color);
    	scores.push_back(getScore(copy,moves[i],side));
    	delete copy;
    }

    int max_score = -900000;
    int min_score = 900000;
    for(unsigned int i = 0; i < scores.size(); i++)
    {
    	if(scores[i] > max_score)
    		max_score = scores[i];
    	if(scores[i] < min_score)
    		min_score = scores[i];
    }
    if(side == color)
    	return max_score;
    return min_score;
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
 
int Player::getScore(Board *board,Move *move, Side side)
{
	int score = board->countBlack() - board->countWhite();

	if(side == WHITE)
		score = board->countWhite() - board->countBlack();
	
	if(corner(move))
		score *= 5;
	if(cornerAccess(move))
		score *= -5;

	return score;
}

bool Player::cornerAccess(Move *move)
{
	if(move->getX() == 0)
	{
		if(move->getY() == 1 || move->getY() == 6)
			return true;
	}
	else if(move->getX() == 1)
	{
		if(move->getY() == 0 || move->getY() == 1 || move->getY() == 6 || move->getY() == 7)
			return true;
	}
	else if(move->getX() == 6)
	{
		if(move->getY() == 0 || move->getY() == 1 || move->getY() == 6 || move->getY() == 7)
			return true;
	}
	else if(move->getX() == 7)
	{
		if(move->getY() == 1 || move->getY() == 6)
			return true;
	}
	return false;
}

bool Player::corner(Move *move)
{
	if(move->getX() == 0 && move->getY() == 0)
		return true;
	else if(move->getX() == 0 && move->getY() == 7)
		return true;
	else if(move->getX() == 7 && move->getY() == 0)
		return true;
	else if(move->getX() == 7 && move->getY() == 7)
		return true;

	return false;
}
