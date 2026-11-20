/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkPush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 18:01:01 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 18:01:01 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Move ranks in [first_rank, end_rank) from A to B. */
/* Indices must be assigned. */
void	push_chunk(t_stack *a, t_stack *b, int first_rank, int end_rank)
{
	t_node	*target;
	int		midpoint;

	target = find_chunk_target(a, first_rank, end_rank);
	midpoint = first_rank + (end_rank - first_rank) / 2;
	/* TODO: While target is not NULL: */
	while (target)
	{
		bring_to_top(a, target, 'a');
		op_pb(a, b);
		if (b->top->index < midpoint)
			op_rb(b);
		target = find_chunk_target(a, first_rank, end_rank);
	}
}
