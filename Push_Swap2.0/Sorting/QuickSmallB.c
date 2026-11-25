/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuickSmallB.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:21:08 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Encontra a posicao do maior rank entre os primeiros left nos de B. */
static int	max_position(t_stack *b, int left)
{
	t_node	*scan;
	int		pos;
	int		best_pos;
	int		best_index;

	scan = b->top;
	pos = 0;
	best_pos = 0;
	best_index = -1;
	while (pos < left)
	{
		if (scan->index > best_index)
		{
			best_index = scan->index;
			best_pos = pos;
		}
		scan = scan->below;
		pos++;
	}
	return (best_pos);
}

/* Roda B o numero indicado de vezes no sentido escolhido. */
static void	rotate_b(t_stack *b, int times, int forward)
{
	while (times > 0)
	{
		if (forward)
			op_rb(b);
		else
			op_rrb(b);
		times--;
	}
}

/* Transfere para A o maior rank entre os nos considerados de B. */
static void	pull_top_max(t_stack *a, t_stack *b, int left)
{
	int	pos;

	pos = max_position(b, left);
	if (pos == 1)
		op_sb(b);
	else
		rotate_b(b, pos, 1);
	op_pa(a, b);
	if (pos > 1)
		rotate_b(b, pos, 0);
}

/* Transfere ate tres nos do topo de B para A em ordem crescente. */
void	quick_small_b(t_stack *a, t_stack *b, int n)
{
	while (n > 0)
	{
		pull_top_max(a, b, n);
		n--;
	}
}
