/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuickSmallA.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:21:05 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Ordena os tres nos do topo de A apenas com operacoes permitidas. */
static void	sort_top_three(t_stack *a)
{
	int	x;
	int	y;
	int	z;

	x = a->top->index;
	y = a->top->below->index;
	z = a->top->below->below->index;
	if (x < y && y < z)
		return ;
	if (x < z && z < y)
		return (op_ra(a), op_sa(a), op_rra(a));
	if (y < x && x < z)
		return (op_sa(a));
	if (y < z && z < x)
		return (op_sa(a), op_ra(a), op_sa(a), op_rra(a));
	if (z < x && x < y)
		return (op_ra(a), op_sa(a), op_rra(a), op_sa(a));
	op_sa(a);
	op_ra(a);
	op_sa(a);
	op_rra(a);
	op_sa(a);
}

/* Ordena os dois ou tres nos do topo de A sem alterar os restantes. */
void	quick_small_a(t_stack *a, int n)
{
	if (n == 2 && a->top->index > a->top->below->index)
		op_sa(a);
	else if (n == 3)
		sort_top_three(a);
}
