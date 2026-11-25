/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkPush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:01:01 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:20:38 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Envia para B todos os ranks da janela, escolhendo o mais proximo em A. */
void	push_chunk(t_stack *a, t_stack *b, int first_rank, int end_rank)
{
	t_node	*target;
	int		midpoint;

	target = find_chunk_target(a, first_rank, end_rank);
	midpoint = first_rank + (end_rank - first_rank) / 2;
	while (target)
	{
		bring_to_top(a, target, 'a');
		op_pb(a, b);
		if (b->top->index < midpoint)
			op_rb(b);
		target = find_chunk_target(a, first_rank, end_rank);
	}
}
