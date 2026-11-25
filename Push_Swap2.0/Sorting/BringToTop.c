/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BringToTop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:10:01 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:20:13 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Leva um no pertencente a s ao topo usando o sentido de menor custo. */
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
