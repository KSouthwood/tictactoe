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

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <stdbool.h>

/*
 * gameboard is organized as so:
 *
 * tl | tc | tr
 * ---+----+---
 * ml | mc | mr
 * ---+----+---
 * bl | bc | br
 *
 */
typedef struct gameboard
{
	char tl;
	char tc;
	char tr;
	char ml;
	char mc;
	char mr;
	char bl;
	char bc;
	char br;
} gameboard;

typedef struct statistics
{
	unsigned int p1win;
	unsigned int p2win;
	unsigned int draws;
} statistics;

typedef enum output_flag
{
	NONE, NCURSES, TERMINAL
} output_type;

typedef struct flags
{
	unsigned short int plnum;
	unsigned short int players;
	output_type print_output;
} flags;

#endif /* TICTACTOE_H_ */
