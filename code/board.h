#ifndef _BOARD_H
#define _BOARD_H

#include "global.h"
#include "move.h"
/**********************************************************/

/* Position struct to store board, score and player's turn */
typedef struct
{
	char board[ BOARD_ROWS ][ BOARD_COLUMNS ];
	char score[ 2 ];
	char turn;

	int ants[2];			// posa murmigkia uparxoun
	int dead_diff[2];		// posa pe8ainoun kata thn leitourgia tou algori8mou
	int food_diff[2];		// posa faghta trwei o ka8enas kata thn leitourgia tou algori8mou
	int heurestic_value;	// gia to apotelesma ths euretikhs sunarthshs
} Position;


/**********************************************************/

//initializes position
void initPosition( Position * pos );

//prints board
void printBoard( char board[ BOARD_ROWS][ BOARD_COLUMNS ] );

// Prints board along with Player's turn and score
void printPosition( Position * pos );

//plays moveToDo on position pos
//Caution!!! does not check if it is legal! Simply does the move!
void doMove( Position * pos, Move * moveToDo );

// kanei to idio me thn doMove alla dinei panta pontous to fai. Epishs 8umatai posa 
void doMove2( Position * pos, Move * moveToDo );

// returns 1 if we can jump to the left 2 if we can jump to the right 3 if we can jump both directions and 0 if no jump is possible
// row,col can be empty. So it can also be used to determine if we can make a jump from a position we do not occupy
//Caution!!! does no checks if we are inside the board
int canJump( char row, char col, char player, Position * pos );

// like canJump() it doesn't need row, col to be occupied by a piece.
// Caution!!! does no checks if we are inside board
int canJumpTo( char row, char col, char player, Position * pos, char rowDest, char colDest );

// determines if player can move
int canMove( Position * pos, char player );

// determines if a move is legal
int isLegal( Position * pos, Move * moveToCheck );

#endif