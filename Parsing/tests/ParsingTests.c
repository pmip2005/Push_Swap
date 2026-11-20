/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingTests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-18 23:05:37 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-18 23:05:37 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parsing.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static void	valid(const char *text, int expected)
{
	int	value;

	value = 123;
	assert(parse_int(text, &value) == 1);
	assert(value == expected);
}

static void	invalid(const char *text)
{
	int	value;

	value = 123;
	assert(parse_int(text, &value) == 0);
	assert(value == 123);
}

static void	test_split(void)
{
	char	**tokens;
	char	*part;

	tokens = ft_split(",one,,two,", ',');
	assert(tokens && tokens[0] && tokens[1] && !tokens[2]);
	assert(!strcmp(tokens[0], "one") && !strcmp(tokens[1], "two"));
	free_tokens(tokens);
	tokens = split_whitespace(" \t3\n-2\r+1\v\f ");
	assert(tokens && tokens[0] && tokens[1] && tokens[2] && !tokens[3]);
	assert(!strcmp(tokens[0], "3") && !strcmp(tokens[1], "-2"));
	assert(!strcmp(tokens[2], "+1"));
	free_tokens(tokens);
	tokens = split_whitespace(" \t\n");
	assert(tokens && !tokens[0]);
	free_tokens(tokens);
	tokens = ft_split("", ' ');
	assert(tokens && !tokens[0]);
	free_tokens(tokens);
	assert(!ft_split(NULL, ' ') && !split_whitespace(NULL));
	free_tokens(NULL);
	part = ft_substr("abc", 100, 5);
	assert(part && !*part);
	free(part);
	puts("[PASS] Imported split, whitespace normalization and token cleanup");
}

int	main(void)
{
	const char	*bad[] = {"", "+", "-", " 12", "12 ", "\t12", "12\n",
		"- 12", "+ 12", "++12", "--12", "+-12", "12x", "x12", "1.2",
		"2147483648", "-2147483649", "999999999999999999999999999999"};
	char		large[10001];
	size_t		i;

	valid("0", 0);
	valid("+0", 0);
	valid("-0", 0);
	valid("42", 42);
	valid("+12", 12);
	valid("-12", -12);
	valid("00042", 42);
	valid("2147483647", INT_MAX);
	valid("-2147483648", INT_MIN);
	puts("[PASS] Signs, zero, leading zeros and integer boundaries");
	i = 0;
	while (i < sizeof(bad) / sizeof(bad[0]))
		invalid(bad[i++]);
	invalid(NULL);
	assert(parse_int("12", NULL) == 0);
	puts("[PASS] Invalid tokens, whitespace, range errors and null pointers");
	memset(large, '9', 10000);
	large[10000] = '\0';
	invalid(large);
	memset(large, '0', 10000);
	valid(large, 0);
	large[9999] = '7';
	valid(large, 7);
	puts("[PASS] 10,000-digit input without overflow or truncation");
	test_split();
	puts("All parsing tests passed.");
	return (0);
}
