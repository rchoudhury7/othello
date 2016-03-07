#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    Board *newBoard = new Board();
    Side color = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	//comment for commit
    delete newBoard;
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
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    if (Board::checkMove(*opponentsMove, ?) == false) {
        stderr("invalid move");
    }
    int score = 0;
    int currScore = 0;
    Move *bestMove, *currMove;
    for (int i = 0; i < legMoves1.size(); ++i) {
      Board *boardCopy = Board::*newboard.copy();
      *currMove = legMoves1[i];
      *boardCopy.doMove(legMoves1[i] ,color)
      // Now we need to find a list of legal after move on boardCopy
      for (int j = 0; j < legMoves[2].size(); ++j) {
        Board *boardCopy2  = Board::*boardCopy.copy();
        if (side == BLACK) {
          *boardCopy2.doMove(legMoves2[j], WHITE);
          currScore = boardCopy2.countBlack() - boardCopy2.countWhite();
        }
        else {
          *boardCopy2.doMove(legMoves2[j], BLACK);
          currScore = boardCopy2.countwhite() - boardCopy2.countBlack();
        }
	if (currScore > score) {
	  score = currScore;
	  *bestMove = *currMove;
	}
      }
    }
    return *bestMove;
}
