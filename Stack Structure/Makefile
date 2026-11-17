NAME := stack_tests
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined
LDFLAGS := -fsanitize=address,undefined

SRCS := StackTests.c StackBehaviours.c StackBehaviours2.c \
	StackChecks.c NodeBehaviours.c
OBJS := $(SRCS:.c=.o)

.PHONY: all test clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c StackStruct.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
