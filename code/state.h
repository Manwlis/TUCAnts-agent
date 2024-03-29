#ifndef _STATE_H
#define _STATE_H

#include "global.h"
#include "board.h"
#include "move.h"

// gia thn eksagwgh statistikwn
#define LOGGING 0

#define SEARCH_DEPTH 11

#define A_B_PRUNING_ACTIVE 1
#define MOVE_REORDER_ACTIVE 1

#define NO_STOP_AT_VOLATILE 1
#define VOLATILE_MAX_DEPTH SEARCH_DEPTH+5

#define MULTITHREDING 1

// 8ewritika mexri 24 kiniseis, praktika den exw dei panw apo 15
#define MAX_LEGAL_MOVES 25

/** Ws state, 8ewrw ena stigmaiothpo tou board meta apo ka8e kinish.
 * Den xreiazomai parapanw plhroforia apo to Position, gia auto den uparxei struct state.
 * Gia na dhmiourgh8ei nea katastash (neo Position) ginetai pass by value.
 */

// plhroforia ka8e thread kata thn parallhlopoihsh ths anazhthshs.
typedef struct
{
    Position position;
    int value;
} Thread_data;

char goodies_color;
char badies_color;

// statistics
int max_depth;
int min_num;
int max_num;
int over_limit;


/**********************************************************/
/******************** Minimax methods *********************/
/**********************************************************/

void minimax_decision( Position* position , Move* move );

int max_value( Position position , int depth , int a , int b );

int min_value( Position position , int depth , int a , int b );

int terminal_test( Position* position , int depth , int jump_flag );

int utility( Position* position , int jump_flag );


/**********************************************************/
/******************** Utility methods *********************/
/**********************************************************/

/** Briskei oles tis dunates kiniseis kai tis bazei ston pinaka legal_moves. Epistrefei to plh8os tous. */
int find_moves_white( Position* position , Move* legal_moves , int jump_flag );
int find_moves_black( Position* position , Move* legal_moves , int jump_flag );

/** Briskei oles tis nees katastaseis apo tis kinhseis sto pinaka move_array. Tis bazei ston pinaka new_positions. */
void do_moves_and_reorder( Position* restrict position , Position* new_positions , Move* move_array , int moves_num );

/** Metraei posa pionia tou sugkekrimenou xrwmatos uparxoun. */
inline int count_pieces( Position* restrict position , char color )
{
	int num_pieces = 0;
	for( int i = 0; i < BOARD_ROWS; i++ )
		for( int j = 0; j < BOARD_COLUMNS; j++ )
			if( position->board[ i ][ j ] == color )
				num_pieces++;
	return num_pieces;
}

/** Elenxei an uparxei dunato pidima gia auton pou paizei. */
inline int jump_possible ( Position* restrict position )
{
    for( int i = 0; i < BOARD_ROWS; i++ )
        for( int j = 0; j < BOARD_COLUMNS; j++ )
            if( position->board[ i ][ j ] == position->turn ) // autounou pou paizei
                if( canJump( i , j , position->turn , position ) )
                    return TRUE;
    return FALSE;
}

/** Epistefei thn kateu8unsh tou paixth pou paizei. +-1 */
inline int player_direction( Position* restrict pos )
{
    if( pos->turn == WHITE )		// find movement's direction
        return 1;
    else
        return -1;
}

// gia to reorder.
inline int heurestic_value( Position* restrict position , int jump_flag )
{
	// exei geinei h allagh gurou otan kaleitai h euretikh. Prepei na ta koitaksw anapoda
	// posa pe8anan + posa efage - mporei na pidiksei o antipalos
	return position->dead_diff[ position->turn ] * 2 + position->food_diff[ getOtherSide(position->turn) - jump_flag * 2 ];
}

// gia thn qsort ths reorder.
int comparitor( const void * lhs , const void * rhs );


/**********************************************************/
/********************** Data movers ***********************/
/**********************************************************/

/** Copy source Move to target Move. */
inline void copy_move( Move* restrict source , Move* restrict target )
{
	for (int i = 0 ; i < 2 ; i++ )
		for (int j = 0 ; j < MAXIMUM_MOVE_SIZE ; j++ )
			target->tile[i][j] = source->tile[i][j];

	target->color = source->color;	
}

/** Copy source Position to target Position. */
inline void copy_position( Position* restrict source , Position* restrict target )
{
	for ( int i = 0 ; i < BOARD_ROWS ; i++ )
		for (int j = 0 ; j < BOARD_COLUMNS ; j++ )
			target->board[i][j] = source->board[i][j];

	target->score[BLACK] = source->score[BLACK];
	target->score[WHITE] = source->score[WHITE];
	target->turn = source->turn;

    target->food_diff[BLACK] = source->food_diff[BLACK];
    target->food_diff[WHITE] = source->food_diff[WHITE];

	target->dead_diff[BLACK] = source->dead_diff[BLACK];
	target->dead_diff[WHITE] = source->dead_diff[WHITE];

	target->ants[BLACK] = source->ants[BLACK];
	target->ants[WHITE] = source->ants[WHITE];
}

void* thread_work( void* param );

#endif