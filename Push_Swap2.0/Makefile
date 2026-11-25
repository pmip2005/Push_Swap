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

NAME := push_swap
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Keep compiled object files in one folder instead of beside the sources.
BUILD := .build

# Source filenames, grouped by their folder. The rules below locate each file.
STACK_SRCS := \
	StackBehaviours.c \
	StackBehaviours2.c \
	StackChecks.c \
	NodeBehaviours.c

OPERATION_SRCS := \
	Swap.c \
	Push.c \
	Rotate.c \
	ReverseRotate.c

SORTING_SRCS := \
	SortThree.c \
	SortFive.c \
	BringToTop.c \
	ChunkAssignIndices.c \
	ChunkFindTarget.c \
	ChunkPush.c \
	ChunkPullMax.c \
	ChunkSort.c \
	QuickSort.c \
	QuickSmallA.c \
	QuickSmallB.c \
	QuickSplit.c

PARSING_SRCS := \
	ParseInt.c \
	ParseArguments.c \
	AppendArgument.c \
	AppendToken.c \
	SplitWhitespace.c \
	ft_split.c \
	ft_substr.c \
	ft_strlen.c

SRCS := \
	main.c \
	StrategyFlag.c \
	$(STACK_SRCS) \
	$(OPERATION_SRCS) \
	$(SORTING_SRCS) \
	$(PARSING_SRCS)

# Turn each filename into an object path: main.c becomes .build/main.o.
# Source filenames must be unique across the folders.
OBJS := $(SRCS:%.c=$(BUILD)/%.o)

# Recompile when a project header changes. Escape the space in Stack Structure.
HEADERS := \
	PushSwap.h \
	Parsing/Parsing.h \
	Sorting/Sorting.h \
	Operations/Operations.h \
	Stack\ Structure/StackStruct.h

# These are commands, not names of files that Make should look for.
.PHONY: all test test-sanitize clean fclean re

all: $(NAME)

# Link the object files into the executable. $@ means the target's name.
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD):
	mkdir -p $@

# Compile one source at a time. % matches its filename without the extension.
# $< is the source path; $@ is the resulting object path.
# After |, BUILD must exist but its timestamp does not trigger recompilation.
$(BUILD)/%.o: %.c $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILD)/%.o: Stack\ Structure/%.c $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILD)/%.o: Operations/%.c $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILD)/%.o: Sorting/%.c $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILD)/%.o: Parsing/%.c $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CFLAGS) -c "$<" -o $@

# Build the program, then run the section tests and command-line tests.
test: $(NAME)
	$(MAKE) -C "Stack Structure/tests" test
	$(MAKE) -C Parsing/tests test
	$(MAKE) -C Sorting/tests test
	python3 tests/test_cli.py

# Test the complete program with memory and undefined-behavior checks.
test-sanitize:
	$(MAKE) NAME=tests/push_swap_sanitized BUILD=.build-sanitized \
		CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address,undefined" all
	python3 tests/test_cli.py --binary tests/push_swap_sanitized

# RM is Make's built-in removal command. Only generated files are removed.
clean:
	$(RM) $(OBJS)
	$(RM) .build-sanitized/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) tests/push_swap_sanitized

re:
	$(MAKE) fclean
	$(MAKE) all
