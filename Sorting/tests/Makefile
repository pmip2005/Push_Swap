NAME := sorting_tests
CC := cc
PYTHON := python3
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined

STACK := ../../Stack\ Structure
SRCS := SortingTests.c ../SortThree.c ../SortFive.c ../BringToTop.c \
	../../Operations/Swap.c ../../Operations/Push.c \
	../../Operations/Rotate.c ../../Operations/ReverseRotate.c \
	$(STACK)/StackBehaviours.c $(STACK)/StackBehaviours2.c \
	$(STACK)/StackChecks.c $(STACK)/NodeBehaviours.c
HEADERS := ../Sorting.h ../../Operations/Operations.h $(STACK)/StackStruct.h

.PHONY: all test clean fclean re

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(SRCS) -o $@

test: $(NAME)
	$(PYTHON) test_sorting.py

clean:
	$(RM) $(NAME)

fclean: clean

re:
	$(MAKE) fclean
	$(MAKE) all
