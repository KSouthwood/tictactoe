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

#include "console_output.h"

#include <stdio.h>

const char VERT_LINE[] = {0xe2, 0x94, 0x83, 0x00};
const char HORZ_LINE[] = {0xe2, 0x94, 0x81, 0x00};
const char VERT_HORZ[] = {0xe2, 0x95, 0x8b, 0x00};

/*
 * Print out the gameboard
 *
 * Prints out a gameboard object passed to it
 */
void printboard_console(gameboard board, statistics *stats)
{
	char *line_format = "%2$c" ANSI_COLOR_YELLOW "%1$s" ANSI_COLOR_RESET "%3$c"
			ANSI_COLOR_YELLOW "%1$s" ANSI_COLOR_RESET "%4$c";
	char *sepr_format = ANSI_COLOR_YELLOW "%1$s%2$s%1$s%2$s%1$s\n" ANSI_COLOR_RESET;
	char *stat_format = ANSI_COLOR_CYAN "\t%s%i\n" ANSI_COLOR_RESET;

	printf("\n");
	printf(line_format, VERT_LINE, board.tl, board.tc, board.tr);
	printf(stat_format, "Player 1: ", stats->p1win);
	printf(sepr_format, HORZ_LINE, VERT_HORZ);
	printf(line_format, VERT_LINE, board.ml, board.mc, board.mr);
	printf(stat_format, "Player 2: ", stats->p2win);
	printf(sepr_format, HORZ_LINE, VERT_HORZ);
	printf(line_format, VERT_LINE, board.bl, board.bc, board.br);
	printf(stat_format, "Draws   : ", stats->draws);
}

/*
 * Prints the game instructions
 *
 * Print out the instructions for playing the game
 */
void instructions_console()
{
	printf("Tic-tac-toe\n\n");
	printf("Two players take turns choosing boxes on the board. First to get three in a row\n");
	printf("- horizontally, vertically or diagonally - is the winner. If no-one is successful,\n");
	printf("it's a draw. Each successive game is started by the next player to play.\n");

	return;
}
