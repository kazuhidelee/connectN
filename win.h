#ifndef WIN_H
	#define WIN_H
	#include <stdbool.h>
	bool array_has_win(char* array, char winning_char, int pieces_to_win, int array_len);
	bool someone_won_horizontally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool someone_won_vertically(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool someone_won_left_diagonally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool someone_won_right_diagonally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool someone_won_diagonally(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool is_game_over(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool someone_won(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);
	bool tie(char** board, int num_rows, int num_cols, char blank_char, int pieces_to_win);

#endif
