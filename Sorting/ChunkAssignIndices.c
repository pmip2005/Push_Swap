/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkAssignIndices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 16:08:08 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 16:08:08 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

void	assign_indices(t_stack *a)
{
	t_node	*current;
	t_node	*scan;

	current = a->top;
	scan = a->top;
	while (current)
	{
		current->index = 0;
		while (scan)
		{
			if (scan->value < current->value)
				current->index++;
			scan = scan->below;
		}
		current = current->below;
		scan = a->top;
	}
}
