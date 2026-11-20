/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BringToTop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-18 22:10:01 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-18 22:10:01 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Move target to the top of stack s. Target must belong to s. */
/* Use 'a' or 'b' to select the stack's rotation instructions. */
void	bring_to_top(t_stack *s, t_node *target, char stack)
{
	t_node	*i;
	int		pos;
	void	(*rotate)(t_stack *);

	pos = 0;
	i = s->top;
	while (i && i != target)
	{
		pos++;
		i = i->below;
	}
	if (!i || (stack != 'a' && stack != 'b'))
		return ;
	rotate = op_rra;
	if (stack == 'b')
		rotate = op_rrb;
	if (forward_is_cheaper(pos, s->size))
	{
		rotate = op_ra;
		if (stack == 'b')
			rotate = op_rb;
	}
	while (target != s->top)
		rotate(s);
}
