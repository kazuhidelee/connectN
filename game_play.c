#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_play.h"
#include "board.h"
#include "win.h"
#include "input_validation.h"

/**
* Returns the starting player.
* @return: 0 meaning player 1 starts first
*/
int get_starting_player_turn(){
	return 0; //0 means player 1, 1 means player 2
}

/**
* Puts player pieces in a string, player 1 being first.
* @return: string of player pieces
*/
char* get_player_pieces(){
	char* player_pieces = (char*)calloc(3, sizeof(char));
	strcpy(player_pieces, "XO");
	return player_pieces;
}

/**
* Sets up game by getting all info needed for new game (empty board, starting player, player pieces)
* @param num_rows: number of rows in board
* @param num_cols: number of columns in board
* @param pieces_to_win: number of pieces in a row needed to win
* @param blank_char: character used to indicate there is no play at a space
* @param out_board: pointer for empty board
* @param out_starting_player_turn: pointer for starting player
* @param out_player_pieces: pointer for string containing player pieces
*/
void setup_game(int num_rows, int num_cols, int pieces_to_win, char blank_char, char** *out_board,
								int *out_starting_player_turn, char* *out_player_pieces){
	char** board = create_empty_board(num_rows, num_cols, blank_char);
	int player_turn = get_starting_player_turn();
	char* player_pieces = get_player_pieces();
	*out_board = board;
	*out_starting_player_turn = player_turn;
	*out_player_pieces = player_pieces;
}

/**
* Current player takes turn. Board is printed and player takes move.
* @param board: board of current state of game
* @param num_rows: number of rows in board
* @param num_cols: number of columns in board
* @param blank_char: character used to show there is no play on this position
* @param cur_player_piece: player piece of current player
*/
void cur_player_take_turn(char** board, int num_rows, int num_cols, char blank_char, char cur_player_piece){
	int move_row, move_col;
	print_board(board, num_rows, num_cols);
	get_valid_move_from_player(board, num_rows, num_cols, blank_char, &move_row, &move_col);
	place_piece(cur_player_piece, board, move_row, move_col);
}

/**
* Keep asking user to enter a move until the user enter a valid move
* @param board: board that will be used in the game
* @param num_rows: numbers of rows on the board
* @param num_cols: numbers of columns on the board
* @param blank_char: character that represents the empty space on board
* @param out_move_row: pointer pointing to the row the player placed their piece in
* @param out_move_col: pointer pointing to the column the player placed their piece in
*/
void get_valid_move_from_player(char** board, int num_rows, int num_cols, char blank_char,
																int *out_move_row, int*out_move_col){
	int num_args_read = 1;
	do{
		printf("Enter a column between %d and %d to play in: ", 0, num_cols - 1);
		num_args_read = scanf("%d", out_move_col);
	}while(!is_valid_move(num_args_read, board, num_rows, num_cols, blank_char, *out_move_col));

	*out_move_row = get_move_row(board, num_rows, num_cols,*out_move_col, blank_char);
}

/**
* Gets row index of current move. AKA row index of blank char closest to top in column.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: move row index
*/
int get_move_row(char** board, int num_rows, int num_cols, int move_col, char blank_char){
	char* column = get_column(board, num_rows, num_cols, move_col);
	for(int i = 0; i < sizeof(column); ++i){
		if (column[i] == blank_char){
			return i;
		}
	}
	return 0;
}

/**
* Check whether if the move player trying to make is valid
* @param num_args_read: numbers of argument that user to enter
* @param board: board that will be used in the game
* @param num_rows: numbers of rows on the board
* @param num_cols: numbers of columns on the board
* @param blank_char: character that represents the empty space on board
* @param move_col: the column player wants to place their piece in
* @return: return true if it is a valid move, return false otherwise
*/
bool is_valid_move(int num_args_read, char** board, int num_rows, int num_cols, char blank_char, int move_col){
	const int num_args_needed = 1;

	return isValidFormat(num_args_read, num_args_needed) &&
					col_is_on_board(num_cols, move_col) &&
					is_col_open(board, num_rows, num_cols, move_col, blank_char);

}

/** Change turn between player 1 and player 2
* @param cur_player_turn: the turn of the current player
* @param number_of_players: the number of player in the game
*/
void change_turns(int* cur_player_turn, int number_of_players){
	*cur_player_turn = (*cur_player_turn + 1 ) % number_of_players;
}

/** 
* Determine the winner of the game and announce the result
* @param board: board that will be used in the game
* @param num_rows: numbers of rows on the board
* @param num_cols: numbers of columns on the board
* @param blank_char: character that represents the empty space on board
* @param cur_plyer_turn: the turn of the current player
* @param pieces_to_win: pieces players have to connect on the board in order to win the connect n
*/
void announce_results(char** board, int num_rows, int num_cols, char blank_char, int cur_player_turn, int pieces_to_win){
	if(someone_won(board, num_rows, num_cols, blank_char, pieces_to_win)){
			if(cur_player_turn == 0){
				printf("Player 1 Won!\n");
			}else{
				printf("Player 2 Won!\n");
			}
	}else{
		printf("Tie game!\n");
	}

}

/**
* start the game play of connect n
* @param board: board that will be used in the game
* @param num_rows: numbers of rows on the board
* @param num_cols: numbers of columns on the board
* @param pieces_to_win: pieces players have to connect on the board in order to win the connect n
* @param blank_char: character that represents the empty space on board
* @param starting_plyer_turn: the turn of the starting player
* @param player_pieces: pieces that represents player
*/
void play_game(char** board, int num_rows, int num_cols, int pieces_to_win, char blank_char, int starting_player_turn,
               char* player_pieces){
	int cur_player_turn = starting_player_turn;
	const int num_players = 2;
	while(true){
		cur_player_take_turn(board, num_rows, num_cols, blank_char, player_pieces[cur_player_turn]);
		if(is_game_over(board, num_rows, num_cols, blank_char, pieces_to_win)){
			break;
		}
		change_turns(&cur_player_turn, num_players);
	}
	print_board(board, num_rows, num_cols);
	announce_results(board, num_rows, num_cols, blank_char, cur_player_turn, pieces_to_win);
}

/**
* Clean up everything that was made for the game, including the boar and players' pieces
* @param board: the board used in the game
* @param num_rows: numbers of rows on the board
* @param num_cols: numbers of columns on the board
* @param player_pieces: player's pieces used in the game
*/
void clean_up(char** board, int num_rows, int num_cols, char* player_pieces){
	delete_board(board, num_rows);
	free(player_pieces);
}


