#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/**
* Create an empty board filled with the blank characters with the numbers of rows and columns user entered
* @param num_rows: numbers of rows of the empty board 
* @param num_cols: numbers of columns of the empty board
* @param blank_char: the blank character that represents the space is empty
* @return: empty board with num_rows rows and num_cols cols
*/
char** create_empty_board(int num_rows, int num_cols, char blank_char){
	char** board = (char**)calloc(num_rows, sizeof(char*));
	for(int i = 0; i < num_rows; ++i){
		board[i] = (char*)calloc(num_cols, sizeof(char));
		for(int j = 0; j < num_cols; ++j){
			board[i][j] = blank_char;
		}
	}
	return board;
}


/** 
* Prints board, order of rows on board is reversed when shown to user.
* @param board: board of current game
* @param num_rows: number of rows of board
* @param num_cols: number of columns of board
* @return: none
*/
void print_board(char** board, int num_rows, int num_cols){
	//print the boards contents
	for(int i = num_rows-1; i >= 0; --i){
		printf("%d ", i);
		for(int j = 0; j < num_cols; ++j){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}

	//print the column headers
		printf("  ");
	for(int i = 0; i < num_cols; ++i){
		printf("%d ", i);
	}
	printf("\n");

}

/**
* Delete the board created using calloc
* @param board: the board user wants to delete
* @param num_rows: numbers of rows of the board
*/
void delete_board(char** board, int num_rows){
	for(int i = 0 ; i < num_rows; ++i){
		free(board[i]);
	}
	free(board);
}

/**
* Places current player piece on the board on the move coordinates passed into function.
* @param piece: character of piece being placed (X for P1, O for P2)
* @param board: board of current play in game
* @param row: row position of move player wants to make
* @param column: column position of move player wants to make
*/
void place_piece(char piece, char** board, int row, int col){
	board[row][col] = piece;
}

/** 
* Detect whether the player's move is on the column 
* @param num_cols: numbers of columns on the board
* @param col: the column user is trying to place their piece on
* @return: true if it's on the column, false if it is out of bound
*/
bool col_is_on_board(int num_cols, int col){
	return is_between(col, 0, num_cols - 1);
}

/**
* Checks if there is a blank space on the column for the player to place piece on.
* @param board: board of current play of game
* @param num_rows: number of rows of board
* @param num_cols: number of columns of board
* @param col: desired column to check
* @param blank_char: character used to indicate no play on that position
* @return: false if column is not open, true if open
*/
bool is_col_open(char** board, int num_rows, int num_cols, int col, char blank_char){
	char* column = get_column(board, num_rows, num_cols, col);
	for(int i = 1; i < num_rows; ++i){
		if (column[i] == blank_char){
			return true;
		}
	}
	return false;
}

/**
* Checks if value is between two other values.
* @param value: value to check
* @param min_val: minimum num value can be
* @param max_val: maximum num value can be
* @return: true if value is between min and max, false if it isn't
*/
bool is_between(int value, int min_val, int max_val){
	return value >= min_val && value <= max_val;
}


/* bool all_same(char* values, int len){
	for(int i = 1; i < len; ++i){
		if(values[i] != values[0]){
			return false;
		}
	}
	return true;
} */

/**
* Gets an array of all characters in a column given column coordinate.
* @param board: board of current play of game
* @param num_rows: number of rows of board
* @param num_cols: number of columns of board
* @param col: index of desired column to return
* @return: array of characters in column
*/
char* get_column(char** board, int num_rows, int num_cols, int col){
	char* the_column = (char*)calloc(num_cols, sizeof(char));
	for(int i = 0; i < num_rows; ++i){
		the_column[i] = board[i][col];
	}
	return the_column;
}

/**
* Gets an array of all characters in a right diagonal given starting diagonal coordinate.
		X
	  X      <- Right Diagonal
	X
* @param board: board of current play of game
* @param num_rows: number of rows of board
* @param num_cols: number of columns of board
* @param start_row: row index to start on
* @param start_col: column index to start on
* @param diag_length: length of diagonal to return
* @return: array of characters in column
*/
char* get_right_diagonal(char** board, int num_rows, int num_cols, int start_row, int start_col, int* diag_length){
	int biggest_dim;
	if (num_rows > num_cols){
		biggest_dim = num_rows;
	}else{
		biggest_dim = num_cols;
	}
	char* diag = (char*)calloc(biggest_dim, sizeof(char));
	for(int i = 0; ((start_row + i) < num_rows) && ((start_col + i) < num_cols); ++i){
		diag[i] = board[start_row + i][start_col + i];
		(*diag_length) += 1;
	}
	return diag;

}
/**
* Get every element on the left diagnol from the given starting point and put them in an array
* @param board: board of current play of game
* @param num_rows: numbers of rows on the board
* @param num_cols: numbers of columns on the board
* @param start_row: the starting row index 
* @param start_col: the starting column index 
* @param diag_length: length of diagonal to return
* @return: array of characters in column
*/
char* get_left_diagonal(char** board, int num_rows, int num_cols, int start_row, int start_col, int* diag_length){
	int biggest_dim;

	if (num_rows > num_cols) {
		biggest_dim = num_rows;
	}else{
		biggest_dim = num_cols;
	}

	char* diag = (char*)calloc(biggest_dim, sizeof(char));
	for(int i = 0; ((start_row + i) < num_rows) && ((start_col - i) < num_cols); ++i){
		diag[i] = board[start_row + i][start_col - i];
		(*diag_length) += 1;
	}
	return diag;
}

