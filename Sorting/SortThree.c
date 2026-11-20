/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SortThree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-17 17:04:03 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-17 17:04:03 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Sort exactly three distinct values, smallest at the top. */
void	sort_three(t_stack *a)
{
	t_node	*largest;
	t_node	*i;

	if (stack_is_sorted(a))
		return ;
	largest = a->top;
	i = a->top;
	while (i)
	{
		if (i->value > largest->value)
			largest = i;
		i = i->below;
	}
	if (largest == a->top)
		op_ra(a);
	else if (largest != a->bottom)
		op_rra(a);
	if (a->top->value > a->top->below->value)
		op_sa(a);
}
