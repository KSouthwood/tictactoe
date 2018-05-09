/***********************************************************************************
 *  MIT License                                                                    *
 *                                                                                 *
 *  Copyright (c) 2018 Keri Southwood-Smith                                        *
 *                                                                                 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy   *
 *  of this software and associated documentation files (the "Software"), to deal  *
 *  in the Software without restriction, including without limitation the rights   *
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 *  copies of the Software, and to permit persons to whom the Software is          *
 *  furnished to do so, subject to the following conditions:                       *
 *                                                                                 *
 *  The above copyright notice and this permission notice shall be included in all *
 *  copies or substantial portions of the Software.                                *
 *                                                                                 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 *  SOFTWARE.                                                                      *
 ***********************************************************************************/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <wchar.h>

#include "tictactoe.h"
#include "ansi_colors.h"
#include "console_output.h"
#include "parse_args.h"

// Function declarations
void print_instructions();
int get_players(void);
void get_input(char *prompt, char *input, int length);
void game_loop(statistics *stats, flags flag);
gameboard init_board(void);
void printboard(gameboard board, statistics *stats);
void make_move(int play_num, gameboard *board);
bool check_winner(gameboard board);
char update_space(int player);
bool play_again(void);

int main(int argc, char **argv) {
	statistics stats = {0, 0, 0};
	flags fl = {2, 0, NONE};
	parse_args(argc, argv, &fl);
	print_instructions(fl);
	if (fl.players == 0)
	{
		fl.players = get_players();
	}
	game_loop(&stats, fl);
	printf("\nFinal scores:\nPlayer 1: %i\nPlayer 2: %i\nDraws: %i\n", stats.p1win, stats.p2win, stats.draws);
	return 0;
}

/*
 * Prints the game instructions
 *
 * Print out the instructions for playing the game
 */
void print_instructions(flags flag)
{
	switch (flag.print_output) {
		case TERMINAL:
			instructions_console();
			break;
		case NCURSES:
			break;
		default:
			instructions_console();
			break;
	}

	return;
}

/*
 * Get the number of human players
 *
 * Ask for the number of human players playing. Only accepts 1 or 2 as an acceptable input.
 */
int get_players(void)
{
	char num[2];
	int players = 0;

	while (players != 1 && players != 2)
	{
		get_input("How many players (1 or 2)? ", num, sizeof(num));
		players = atoi(num);
	}

	return players;
}

/*
 * Gets input from the player
 *
 * Gets input from the player. Takes a prompt string, a char array to store the returned string, and the
 * number of characters to accept.
 */
void get_input(char *prompt, char *input, int length)
{
	printf("%s", prompt);

	if (fgets(input, length, stdin) != NULL)
	{
		stdin = freopen(NULL, "r", stdin);
	}

	return;
}

void game_loop(statistics *stats, flags flag)
{
	bool play = true;

	while (play)
	{
		gameboard board = init_board();
		int moves = 0;
		bool won = false;

		while (moves < 9 && !won)
		{
			moves++;
			printboard(board, stats);
			flag.plnum += (flag.plnum == 1) ? 1 : -1;
			make_move(flag.plnum, &board);

			if (moves > 4)
			{
				won = check_winner(board);
			}
		}

		printboard(board, stats);

		if (won)
		{
			printf("Player %i won!\n", flag.plnum);
			if (flag.plnum == 1)
			{
				stats->p1win++;
			}
			else
			{
				stats->p2win++;
			}
		}
		else
		{
			printf("It's a draw!!\n");
			stats->draws++;
		}

		play = play_again();
	}
	return;
}

/*
 * Initialize the gameboard
 *
 * Instantiate and initialize to all spaces a gameboard
 */
gameboard init_board(void)
{
	gameboard board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	return board;
}

/*
 * Print out the gameboard
 *
 * Prints out a gameboard object passed to it
 */
void printboard(gameboard board, statistics *stats)
{
	printboard_console(board, stats);
}

/*
 * Gets and validates a move
 *
 * Asks for a move from the player, and makes sure the move is valid.
 * i.e. the space is available
 */
void make_move(int play_num, gameboard *board)
{
	int move = 0;
	bool legal = false;
	char num[2];
	char prompt[30];

	while (!legal || move < 1 || move > 9)
	{
		sprintf(prompt, "What's your move, player %i? ", play_num);
		get_input(prompt, num, sizeof(num));
		move = atoi(num);

		switch (move)
		{
		case 1:
			if (board->tl == ' ')
			{
				board->tl = update_space(play_num);
				legal = true;
			}
			break;
		case 2:
			if (board->tc == ' ')
			{
				board->tc = update_space(play_num);
				legal = true;
			}
			break;
		case 3:
			if (board->tr == ' ')
			{
				board->tr = update_space(play_num);
				legal = true;
			}
			break;
		case 4:
			if (board->ml == ' ')
			{
				board->ml = update_space(play_num);
				legal = true;
			}
			break;
		case 5:
			if (board->mc == ' ')
			{
				board->mc = update_space(play_num);
				legal = true;
			}
			break;
		case 6:
			if (board->mr == ' ')
			{
				board->mr = update_space(play_num);
				legal = true;
			}
			break;
		case 7:
			if (board->bl == ' ')
			{
				board->bl = update_space(play_num);
				legal = true;
			}
			break;
		case 8:
			if (board->bc == ' ')
			{
				board->bc = update_space(play_num);
				legal = true;
			}
			break;
		case 9:
			if (board->br == ' ')
			{
				board->br = update_space(play_num);
				legal = true;
			}
			break;
		default:
			legal = false;
			break;
		}
	}

	return;
}

/*
 * Checks if we have three in a row
 *
 * Check each of the eight ways to win for three in a row. We'll know who the winner is because we
 * run this right after a player has moved. That player is the winner.
 */
bool check_winner(gameboard board)
{
	if (board.tl == board.tc && board.tc == board.tr && board.tr != ' ')
	{
		return true;
	}
	if (board.ml == board.mc && board.mc == board.mr && board.mr != ' ')
	{
		return true;
	}
	if (board.bl == board.bc && board.bc == board.br && board.br != ' ')
	{
		return true;
	}
	if (board.tl == board.ml && board.ml == board.bl && board.bl != ' ')
	{
		return true;
	}
	if (board.tc == board.mc && board.mc == board.bc && board.bc != ' ')
	{
		return true;
	}
	if (board.tr == board.mr && board.mr == board.br && board.br != ' ')
	{
		return true;
	}
	if (board.tl == board.mc && board.mc == board.br && board.br != ' ')
	{
		return true;
	}
	if (board.tr == board.mc && board.mc == board.bl && board.bl != ' ')
	{
		return true;
	}
	return false;
}

char update_space(int player)
{
	return (player == 1) ? 'X' : 'O';
}

bool play_again(void)
{
	char ans[2] = {'x', '\0'};

	while (strcasecmp(ans, "y") && strcasecmp(ans, "n"))
	{
		get_input("Would you like to play another game? (y/n) ", ans, sizeof(ans));
	}

	if (strcasecmp(ans, "y") == 0)
	{
		return true;
	}

	return false;
}
