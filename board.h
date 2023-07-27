#ifndef BOARD_H
	#define BOARD_H
	#include <stdbool.h>
	char** create_empty_board(int num_rows, int num_cols, char blank_char);
	void print_board(char** board, int num_rows, int num_cols);
	void delete_board(char** board, int num_rows);
	void place_piece(char piece, char** board, int row, int col);
	bool col_is_on_board(int num_cols, int col);
	bool is_col_open(char** board, int num_rows, int num_cols, int col, char blank_char);
	bool is_between(int value, int min_val, int max_val);
	bool all_same(char* values, int len);
	char* get_column(char** board, int num_rows, int num_cols, int col);
	char* get_right_diagonal(char** board, int num_rows, int num_cols, int start_row, 
							int start_col, int* diag_length);
	char* get_left_diagonal(char** board, int num_rows, int num_cols, int start_row, 
							int start_col, int* diag_length);

#endif
