/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkPullMax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 18:34:30 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Move the largest-ranked node from B onto A. */
void	pull_max(t_stack *a, t_stack *b)
{
	t_node	*scan;
	t_node	*largest;

	if (!b->size)
		return ;
	scan = b->top;
	largest = b->top;
	while (scan)
	{
		if (scan->index > largest->index)
			largest = scan;
		scan = scan->below;
	}
	bring_to_top(b, largest, 'b');
	op_pa(a, b);
}
