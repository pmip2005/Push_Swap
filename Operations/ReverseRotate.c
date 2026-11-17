/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseRotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-17 16:37:23 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-17 16:37:23 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operations.h"

void	op_rra(t_stack *a)
{
	if (a->size < 2)
		return ;
	stack_reverse_rotate(a);
	write (1, "rra\n", 4);
}

void	op_rrb(t_stack *b)
{
	if (b->size < 2)
		return ;
	stack_reverse_rotate(b);
	write (1, "rrb\n", 4);
}

void	op_rrr(t_stack *a, t_stack *b)
{
	if (a->size < 2 && b->size < 2)
		return ;
	stack_reverse_rotate(a);
	stack_reverse_rotate(b);
	write(1, "rrr\n", 4);
}
