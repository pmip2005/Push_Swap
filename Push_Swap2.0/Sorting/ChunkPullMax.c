/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkPullMax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:20:34 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Procura em B o no que possui o rank indicado. */
static t_node	*find_rank(t_stack *b, int rank)
{
	t_node	*scan;

	scan = b->top;
	while (scan && scan->index != rank)
		scan = scan->below;
	return (scan);
}

/* Devolve a posicao de target a partir do topo de B. */
static int	pos_of(t_stack *b, t_node *target)
{
	int		pos;
	t_node	*scan;

	pos = 0;
	scan = b->top;
	while (scan != target)
	{
		scan = scan->below;
		pos++;
	}
	return (pos);
}

/* Calcula o menor custo de rotacao para levar target ao topo de B. */
static int	cost_of(t_stack *b, t_node *target)
{
	int	pos;

	pos = pos_of(b, target);
	if (pos < b->size - pos)
		return (pos);
	return (b->size - pos);
}

/* Recupera o maior rank esperado, aproveitando pares consecutivos. */
void	pull_max(t_stack *a, t_stack *b)
{
	t_node	*big;
	t_node	*second;
	int		top_rank;

	if (!b->size)
		return ;
	top_rank = a->size + b->size - 1;
	if (a->size && a->top->index <= top_rank)
		top_rank = a->top->index - 1;
	big = find_rank(b, top_rank);
	second = find_rank(b, top_rank - 1);
	if (second && big && cost_of(b, second) + 1 < cost_of(b, big))
	{
		bring_to_top(b, second, 'b');
		op_pa(a, b);
		bring_to_top(b, big, 'b');
		op_pa(a, b);
		op_sa(a);
		return ;
	}
	bring_to_top(b, big, 'b');
	op_pa(a, b);
}
