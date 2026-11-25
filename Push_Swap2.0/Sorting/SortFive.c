/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SortFive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:54:28 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:21:21 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Reduz A a tres valores, ordena-os e devolve os menores de B. */
void	sort_five(t_stack *a, t_stack *b)
{
	t_node	*smallest;
	t_node	*i;

	if (stack_is_sorted(a))
		return ;
	while (a->size > 3)
	{
		smallest = a->top;
		i = a->top;
		while (i)
		{
			if (i->value < smallest->value)
				smallest = i;
			i = i->below;
		}
		bring_to_top(a, smallest, 'a');
		op_pb(a, b);
	}
	sort_three(a);
	while (b->size)
		op_pa(a, b);
}
