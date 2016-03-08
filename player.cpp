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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
    //should probably implement something to check if the move is valid.
	playBoard->doMove(opponentsMove,oppColor);

    std::vector<int> scores;
    std::vector<Move*> moves = playBoard->getMoves(color);

    for(unsigned int i = 0; i < moves.size(); i++)
    {
    	Board *copy = playBoard->copy();
    	copy->doMove(moves[i],color);
    	scores.push_back(getScore(copy,moves[i]));
    	delete copy;
    }

    int scoreInd = 0;
    for(unsigned int i = 0; i < scores.size(); i++)
    	if(scores[i] > scores[scoreInd])
    		scoreInd = i;
 
    playBoard->doMove(moves[scoreInd],color);
    return moves[scoreInd];
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
 
int Player::getScore(Board *board,Move *move)
{
	int score = board->count(color) - board->count(oppColor);
	
	if(corner(move))
		score *= 3;
	if(cornerAccess(move))
		score *= -3;

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
