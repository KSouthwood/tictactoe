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
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse_args.h"

// Declarations
void parse_args(int argc, char *argv[], flags *flag);

void parse_args(int argc, char *argv[], flags *flag)
{
	printf("Parsing with getopt_long()...\n");
	int option_index = 0;

	static struct option long_options[] =
	{
			{"players", required_argument, 0, 'p'},
			{"help",	no_argument, 0, 'h'},
			{"ncurses",	no_argument, 0, 'n'},
			{"console",	no_argument, 0, 'c'},
			{0, 0, 0, 0}
	};

	int option = 0;

	while (option != -1)
	{
		option = getopt_long(argc, argv, "p:hnc", long_options, &option_index);

		switch (option)
		{
		case 'h':
			printf("Help message was requested.\n");
			break;
		case 'n':
			if (flag->print_output == NONE)
			{
				printf("Setting to NCURSES.\n");
				flag->print_output = NCURSES;
			}
			else
			{
				printf("ncurses & console options are mutually exclusive. Please specify only one option.\n");
			}
			break;
		case 'c':
			if (flag->print_output == NONE)
			{
				printf("Setting to TERMINAL.\n");
				flag->print_output = TERMINAL;
			}
			else
			{
				printf("ncurses & console options are mutually exclusive. Please specify only one option.\n");
			}
			break;
		case 'p':
			printf("Number of players indicated was %s.\n", optarg);
			flag->players = atoi(optarg);
			if (flag->players != 1 && flag->players != 2)
			{
				flag->players = 0;
				printf("Invalid argument supplied. Must be 1 or 2.\n");
			}
			break;
		case -1:
			printf("No more options.\n");
			break;
		default:
			printf("WTF?!\n");
		}
	}

	printf("Finished parsing with getopt_long()...\n\n");
}
