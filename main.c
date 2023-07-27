/*
This program plays a game of Connect N with 2 players given a custom number 
of rows, columns, and pieces in a row needed to win by the user.
*/

#include <stdlib.h>
#include <stdio.h>
#include "game_play.h"


/**
* Main function. Gets arguments of number of rows, number of columns, pieces in a row needed to win.
* @param argc: number of arguments
* @param argv: array of characters user entered
* @return: 0 on successful completion of program, also 0 if user entered invalid input
*/
int main(int argc, char** argv){
	int num_rows, num_cols, pieces_to_win;
	if (argc < 4){
		printf("Not enough arguments entered\n");
		printf("Usage connectn.out num_rows num_columns\nnumber_of_pieces_in_a_row_needed_to_win");
		exit(0);
	}else if(argc > 4){
		printf("Too many arguments entered\n");
		printf("Usage connectn.out num_rows num_columns\nnumber_of_pieces_in_a_row_needed_to_win");
		exit(0);
	}else{
		sscanf(argv[1], "%d", &num_rows);
		sscanf(argv[2], "%d", &num_cols);
		sscanf(argv[3], "%d", &pieces_to_win);
		if((num_rows <= 0)|| (num_cols <= 0)|| (pieces_to_win <= 0)){
			printf("Invalid input");
			exit(0);
		}
	}
	char blank_char = '*';
	char** board;
	char* player_pieces;
	int player_turn;
	setup_game(num_rows, num_cols, pieces_to_win, blank_char, &board, &player_turn, &player_pieces);
	play_game(board, num_rows, num_cols, pieces_to_win, blank_char, player_turn, player_pieces);
	clean_up(board, num_rows, num_cols, player_pieces);
	return 0;

}
