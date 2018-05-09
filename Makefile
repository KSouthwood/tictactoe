PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow

# name for executable
EXE = tictactoe

# space-separated list of header files
HDRS = tictactoe.h console_output.h ansi_colors.h parse_args.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = tictactoe.c console_output.c parse_args.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

all:	$(EXE)

$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
