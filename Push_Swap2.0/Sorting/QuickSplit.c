/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuickSplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:21:17 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Envia os ranks baixos de A para B e devolve quantas vezes rodou A. */
int	split_a(t_stack *a, t_stack *b, int small, int pivot)
{
	int	pushed;
	int	rotated;

	pushed = 0;
	rotated = 0;
	while (pushed < small)
	{
		if (a->top->index < pivot)
		{
			op_pb(a, b);
			pushed++;
		}
		else
		{
			op_ra(a);
			rotated++;
		}
	}
	return (rotated);
}

/* Transfere os ranks altos de B para A e roda os restantes de B. */
int	split_b(t_stack *a, t_stack *b, int big, int pivot)
{
	int	pulled;
	int	rotated;

	pulled = 0;
	rotated = 0;
	while (pulled < big)
	{
		if (b->top->index >= pivot)
		{
			op_pa(a, b);
			pulled++;
		}
		else
		{
			op_rb(b);
			rotated++;
		}
	}
	return (rotated);
}

/* Desfaz as rotacoes para cima aplicadas anteriormente a A. */
void	undo_rotate_a(t_stack *a, int rotated)
{
	while (rotated > 0)
	{
		op_rra(a);
		rotated--;
	}
}

/* Desfaz as rotacoes para cima aplicadas anteriormente a B. */
void	undo_rotate_b(t_stack *b, int rotated)
{
	while (rotated > 0)
	{
		op_rrb(b);
		rotated--;
	}
}
