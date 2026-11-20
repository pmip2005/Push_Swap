/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-17 16:16:47 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-17 16:16:47 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operations.h"

void	op_pa(t_stack *a, t_stack *b)
{
	if (!b->size)
		return ;
	stack_send(b, a);
	write(1, "pa\n", 3);
}

void	op_pb(t_stack *a, t_stack *b)
{
	if (!a->size)
		return ;
	stack_send(a, b);
	write(1, "pb\n", 3);
}
