/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkFindTarget.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:25:19 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:20:27 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"
#include <stddef.h>

/* Indica se a rotacao para cima e mais curta que a rotacao inversa. */
int	forward_is_cheaper(int position, int size)
{
	return (position < size - position);
}

/* Calcula o menor numero de rotacoes para alcancar uma posicao. */
static int	rotation_cost(int position, int size)
{
	if (forward_is_cheaper(position, size))
		return (position);
	return (size - position);
}

/* Escolhe o rank da janela mais barato de levar ao topo de A. */
t_node	*find_chunk_target(t_stack *a, int first_rank, int end_rank)
{
	t_node	*scan;
	t_node	*best_node;
	int		best_cost;
	int		current_cost;
	int		current_position;

	best_node = NULL;
	best_cost = a->size;
	current_position = 0;
	scan = a->top;
	while (scan)
	{
		if (scan->index >= first_rank && scan->index < end_rank)
		{
			current_cost = rotation_cost(current_position, a->size);
			if (!best_node || current_cost < best_cost)
			{
				best_node = scan;
				best_cost = current_cost;
			}
		}
		scan = scan->below;
		current_position++;
	}
	return (best_node);
}
