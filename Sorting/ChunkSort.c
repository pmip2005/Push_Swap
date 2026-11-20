/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 18:34:30 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

static int	chunk_width(int size)
{
	int	root;

	root = 1;
	while ((long long)root * root < size)
		root++;
	return (2 * root);
}

/* Sort A by rank ranges. B must start empty. */
void	chunk_sort(t_stack *a, t_stack *b)
{
	int	width;
	int	first_rank;
	int	end_rank;

	width = chunk_width(a->size);
	assign_indices(a);
	first_rank = 0;
	while (a->size)
	{
		end_rank = first_rank + a->size;
		if (width < a->size)
			end_rank = first_rank + width;
		push_chunk(a, b, first_rank, end_rank);
		first_rank = end_rank;
	}
	while (b->size)
		pull_max(a, b);
}
