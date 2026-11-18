/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BringToTop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-18 22:10:01 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-18 22:10:01 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* target must be a node currently in A. */
void	bring_to_top(t_stack *a, t_node *target)
{
	t_node	*i;
	int		pos;

	pos = 0;
	i = a->top;
	while (i)
	{
		if (i == target)
			break ;
		pos++;
		i = i->below;
	}
	if (pos < a->size - pos)
		while (target != a->top)
			op_ra(a);
	else
		while (target != a->top)
			op_rra(a);
}
