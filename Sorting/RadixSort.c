/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadixSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 18:34:30 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

static void	radix_pass_for_bit(int bit_position, t_stack *a, t_stack *b)
{
	int	starting_size;
	int	processed;

	processed = 0;
	starting_size = a->size;
	while (processed < starting_size)
	{
		if ((a->top->index >> bit_position) & 1)
			op_ra(a);
		else
			op_pb(a, b);
		processed++;
	}
	while (b->size)
		op_pa(a, b);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	bit_position;
	int	max_rank;

	if (a->size < 2)
		return ;
	assign_indices(a);
	max_rank = a->size - 1;
	bit_position = 0;
	while ((max_rank >> bit_position) != 0)
	{
		radix_pass_for_bit(bit_position, a, b);
		bit_position++;
	}
}
