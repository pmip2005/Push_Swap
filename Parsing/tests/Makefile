#  **************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/20 00:54:14 by ppoco             #+#    #+#              #
#    Updated: 2026/11/20 00:54:14 by ppoco            ###   ########.fr        #
#                                                                              #
#  **************************************************************************  #

NAME := parsing_tests
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined
SRCS := ../ParseInt.c ParsingTests.c ../ft_split.c ../ft_substr.c \
	../ft_strlen.c ../SplitWhitespace.c

.PHONY: all test clean fclean re

all: $(NAME)

$(NAME): $(SRCS) ../Parsing.h ../../Stack\ Structure/StackStruct.h Makefile
	$(CC) $(CFLAGS) $(SRCS) -o $@

test: $(NAME)
	./$(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re:
	$(MAKE) fclean
	$(MAKE) all
