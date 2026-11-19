NAME := stack_tests
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined
LDFLAGS := -fsanitize=address,undefined

SRCS := StackTests.c ../StackBehaviours.c ../StackBehaviours2.c \
	../StackChecks.c ../NodeBehaviours.c

.PHONY: all test clean fclean re

all: $(NAME)

$(NAME): $(SRCS) ../StackStruct.h Makefile
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

test: $(NAME)
	./$(NAME)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
