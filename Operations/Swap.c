/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-15 22:41:50 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-15 22:41:50 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operations.h"

void	op_sa(t_stack *a)
{
	if (a->size < 2)
		return ;
	write(1, "sa\n", 3);
	stack_swap(a);
}

void	op_sb(t_stack *b)
{
	if (b->size < 2)
		return ;
	write(1, "sb\n", 3);
	stack_swap(b);
}

void	op_ss(t_stack *a, t_stack *b)
{
	stack_swap(a);
	stack_swap(b);
	if (b->size >= 2 || a->size >= 2)
		write(1, "ss\n", 3);
}
