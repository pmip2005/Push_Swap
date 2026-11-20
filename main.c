/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 00:32:47 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 00:32:47 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PushSwap.h"

static int	same_word(const char *left, const char *right)
{
	while (*left && *left == *right)
	{
		left++;
		right++;
	}
	return (*left == *right);
}

static t_strategy	read_strategy(int *argc, char ***argv)
{
	const char	*flag;

	if (*argc < 2 || (*argv)[1][0] != '-' || (*argv)[1][1] != '-')
		return (ADAPTIVE);
	flag = (*argv)[1];
	if (!same_word(flag, "--simple") && !same_word(flag, "--medium")
		&& !same_word(flag, "--complex") && !same_word(flag, "--adaptive"))
		return (ADAPTIVE);
	(*argc)--;
	(*argv)++;
	if (same_word(flag, "--simple"))
		return (SIMPLE);
	if (same_word(flag, "--medium"))
		return (MEDIUM);
	if (same_word(flag, "--complex"))
		return (COMPLEX);
	return (ADAPTIVE);
}

static t_strategy	adaptive_strategy(t_stack *a)
{
	t_node		*first;
	t_node		*second;
	long long	mistakes;
	long long	total_pairs;

	mistakes = 0;
	first = a->top;
	while (first)
	{
		second = first->below;
		while (second)
		{
			mistakes += (first->value > second->value);
			second = second->below;
		}
		first = first->below;
	}
	total_pairs = (long long)a->size * (a->size - 1) / 2;
	if (mistakes <= (total_pairs - 1) / 5)
		return (SIMPLE);
	if (mistakes <= (total_pairs - 1) / 2)
		return (MEDIUM);
	return (COMPLEX);
}

static void	sort_stack(t_stack *a, t_stack *b, t_strategy strategy)
{
	if (stack_is_sorted(a))
		return ;
	if (a->size == 2 && (strategy == ADAPTIVE || strategy == SIMPLE))
		op_ra(a);
	else if (a->size == 3 && (strategy == ADAPTIVE || strategy == SIMPLE))
		sort_three(a);
	else if (a->size <= 5 && strategy == ADAPTIVE)
		sort_five(a, b);
	else
	{
		if (strategy == ADAPTIVE)
			strategy = adaptive_strategy(a);
		if (strategy == SIMPLE)
			sort_five(a, b);
		else if (strategy == MEDIUM)
			chunk_sort(a, b);
		else
			radix_sort(a, b);
	}
}

int	main(int argc, char **argv)
{
	t_stack		a;
	t_stack		b;
	t_strategy	strategy;

	stack_init(&a);
	stack_init(&b);
	strategy = read_strategy(&argc, &argv);
	if (!parse_arguments(&a, argc, argv))
		return (write(2, "Error\n", 6), 1);
	sort_stack(&a, &b, strategy);
	return (stack_clear(&a), stack_clear(&b), 0);
}
