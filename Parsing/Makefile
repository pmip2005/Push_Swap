NAME := parsing_tests
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined

.PHONY: all test clean fclean re

all: $(NAME)

$(NAME): ParseInt.c ParsingTests.c Parsing.h Makefile
	$(CC) $(CFLAGS) ParseInt.c ParsingTests.c -o $@

test: $(NAME)
	./$(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re:
	$(MAKE) fclean
	$(MAKE) all
