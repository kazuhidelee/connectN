#include <stdbool.h>
#include <stdlib.h>
#include "win.h"
#include "board.h"

/**
* Checks if array has a certain number of winning characters in a row.
* @param array: array to check for win
* @param winning_char: character that has to be in a row to win
* @param pieces_to_win: how many winning characters must be in a row to win
* @param array_len: length of array
* @return: true if array has win, false if not
*/
bool array_has_win(char* array, char winning_char, int pieces_to_win, int array_len){ 
	int count = 0;
	for(int i = 0; i < array_len; ++i){
		if (array[i] == winning_char){
			count += 1;
			if (count == pieces_to_win){
				return true;
			}
		}else{
			count = 0;
		}
	}
	return false;
}

/**
* Checks if there is a winning number of characters in a row horizontally on all rows on the board.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if someone won, false if there is no win
*/
bool someone_won_horizontally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	for(int i = 0; i < num_rows; ++i){
		if (array_has_win(board[i], 'X', pieces_to_win, num_cols) || array_has_win(board[i], 'O', pieces_to_win, num_cols)){
			return true;
		}	
	}
	return false;
}

/**
* Checks if there is a winning number of characters in a column vertically on all columns on the board.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row in the column to determine a win
* @return: true if someone won, false if there is no win
*/
bool someone_won_vertically(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	if (num_rows < pieces_to_win){
		return false;
	}

	for(int i = 0; i < num_cols; ++i){
		char* col = get_column(board, num_rows, num_cols, i);
		if (array_has_win(col, 'X', pieces_to_win, num_rows) || array_has_win(col, 'O', pieces_to_win, num_rows)){
			free(col);
			return true;
		}
		free(col);
	}
	return false;
}

/**
* Checks if there is a winning number of characters in a row diagonally on all right diagonals on the board.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if someone won, false if there is no win
*/
bool someone_won_right_diagonally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	/*
		    X
		  X
		X
	*/
	int diag_length = 0;

	for(int i = 0; i < num_rows; ++i){
		char* diag = get_right_diagonal(board, num_rows, num_cols, 0, i, &diag_length);
		if (array_has_win(diag, 'X', pieces_to_win, diag_length) || array_has_win(diag, 'O', pieces_to_win, diag_length)){
			free(diag);
			return true;
		}
		free(diag);
	}

	for(int i = 0; i < num_cols; ++i){
		char* diag = get_right_diagonal(board, num_rows, num_cols, i, 0, &diag_length);
		if (array_has_win(diag, 'X', pieces_to_win, diag_length) || array_has_win(diag, 'O', pieces_to_win, diag_length)){
			free(diag);
			return true;
		}
		free(diag);
	}
	return false;

}

/**
* Checks if there is a winning number of characters in a row diagonally on all left diagonals on the board.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if someone won, false if there is no win
*/
bool someone_won_left_diagonally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	/*
		X
		  X
			X
	*/
	int diag_length = 0;

	for(int i = 0; i < num_cols; ++i){//change maybe?
		char* diag = get_left_diagonal(board, num_rows, num_rows, 0, i, &diag_length);
		if (array_has_win(diag, 'X', pieces_to_win, diag_length) || array_has_win(diag, 'O', pieces_to_win, diag_length)){
			free(diag);
			return true;
		}
		free(diag);
	}

	for(int i = 0; i < num_rows; ++i){
		char* diag = get_left_diagonal(board, num_rows, num_cols, i, num_cols, &diag_length);
		if (array_has_win(diag, 'X', pieces_to_win, diag_length) || array_has_win(diag, 'O', pieces_to_win, diag_length)){
			free(diag);
			return true;
		}
		free(diag);
	}
	return false;
}

/**
* Determines if someone won on all left or right diagonals.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if someone won, false if there is no win
*/
bool someone_won_diagonally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	return someone_won_left_diagonally(board, num_rows, num_cols, blank_char, pieces_to_win) ||
	 			 someone_won_right_diagonally(board, num_rows, num_cols, blank_char, pieces_to_win);
}

/**
* Determines if game is over.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if game is over, false if game is not over
*/
bool is_game_over(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	return someone_won(board, num_rows, num_cols, blank_char, pieces_to_win) || tie(board, num_rows, num_cols, blank_char, pieces_to_win);
}

/**
* Determines if there is a win on the current board.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if someone won, false if there is no win
*/
bool someone_won(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	return someone_won_vertically(board, num_rows, num_cols, blank_char, pieces_to_win) ||
	someone_won_horizontally(board, num_rows, num_cols, blank_char, pieces_to_win) ||
	someone_won_diagonally(board, num_rows, num_cols, blank_char, pieces_to_win);
}

/**
* Determines if there is a tie on the current board, AKA if the board has no blank chars and there are no wins.
* @param board: board with current play on it
* @param num_rows: number of rows on board
* @param num_cols: number of columns on board
* @param blank_char: piece indicating there is no play on this spot
* @param pieces_to_win: number of pieces that must be in a row to determine a win
* @return: true if there is a tie, false if there is no tie
*/
bool tie(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win){
	if(someone_won(board, num_rows, num_cols, blank_char, pieces_to_win)){
		return false;
	}
	for(int i = 0; i < num_rows; ++i){ //for each row
		for(int j = 0; j <  num_cols; ++j) //for each column/ for each piece in the row
			if(board[i][j] == blank_char){
				return false;
			}
	}
	return true;

}
