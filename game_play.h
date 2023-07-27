#ifndef GAME_PLAY_H
	#define GAME_PLAY_H
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    int get_starting_player_turn();
    char* get_player_pieces();
    void setup_game(int num_rows, int num_cols, int pieces_to_win, char blank_char, char** *out_board,
								int *out_starting_player_turn, char* *out_player_pieces);
    void cur_player_take_turn(char** board, int num_rows, int num_cols, char blank_char, char cur_player_piece);
    void get_valid_move_from_player(char** board, int num_rows, int num_cols, char blank_char,
																int *out_move_row, int*out_move_col);
    int get_move_row(char** board, int num_rows, int num_cols, int move_col, char blank_char);
    bool is_valid_move(int num_args_read, char** board, int num_rows, int num_cols, char blank_char, int move_col);
    void change_turns(int* cur_player_turn, int number_of_players);
    void announce_results(char** board, int num_rows, int num_cols, char blank_char, int cur_player_turn, int pieces_to_win);
    void play_game(char** board, int num_rows, int num_cols, int pieces_to_win, char blank_char, int starting_player_turn,
               char* player_pieces);
    void clean_up(char** board, int num_rows, int num_cols, char* player_pieces);
#endif