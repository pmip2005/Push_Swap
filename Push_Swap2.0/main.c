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

#define QUICK_CHUNK_LIMIT 100

/* Conta inversoes e escolhe a estrategia conforme o nivel de desordem. */
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

/* Deteta se os valores estao em ordem estritamente decrescente. */
static int	is_reverse_sorted(t_stack *a)
{
	t_node	*node;

	node = a->top;
	while (node && node->below)
	{
		if (node->value < node->below->value)
			return (0);
		node = node->below;
	}
	return (1);
}

/* Ajusta a escolha adaptativa aos tamanhos com melhor algoritmo medido. */
static t_strategy	choose_strategy(t_stack *a, t_strategy strategy)
{
	if (strategy != ADAPTIVE)
		return (strategy);
	strategy = adaptive_strategy(a);
	if (a->size >= 500 && is_reverse_sorted(a))
		return (MEDIUM);
	if (strategy == COMPLEX && a->size == QUICK_CHUNK_LIMIT)
		return (MEDIUM);
	if (strategy == MEDIUM && a->size >= 500)
		return (COMPLEX);
	return (strategy);
}

/* Escolhe e executa o algoritmo correspondente a estrategia pedida. */
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
		strategy = choose_strategy(a, strategy);
		if (strategy == SIMPLE)
			sort_five(a, b);
		else if (strategy == MEDIUM)
			chunk_sort(a, b);
		else
			quick_sort(a, b);
	}
}

/* Inicializa as stacks, valida os argumentos, ordena e liberta a memoria. */
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
