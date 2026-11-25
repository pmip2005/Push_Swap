/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-17 16:26:25 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-17 16:26:25 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operations.h"

/* Roda A para cima, passando o topo para o fundo. */
void	op_ra(t_stack *a)
{
	if (a->size < 2)
		return ;
	stack_rotate(a);
	write (1, "ra\n", 3);
}

/* Roda B para cima, passando o topo para o fundo. */
void	op_rb(t_stack *b)
{
	if (b->size < 2)
		return ;
	stack_rotate(b);
	write (1, "rb\n", 3);
}

/* Roda A e B para cima na mesma operacao. */
void	op_rr(t_stack *a, t_stack *b)
{
	if (a->size < 2 && b->size < 2)
		return ;
	stack_rotate(a);
	stack_rotate(b);
	write(1, "rr\n", 3);
}
