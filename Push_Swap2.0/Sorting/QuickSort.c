/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuickSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:21:14 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Ordena em A os n ranks consecutivos iniciados em lo. */
void	quick_sort_a(t_stack *a, t_stack *b, int n, int lo)
{
	int	small;
	int	rotated;

	if (n <= 1)
		return ;
	if (n <= 3)
		return (quick_small_a(a, n));
	small = n / 2;
	rotated = split_a(a, b, small, lo + small);
	if (a->size > n - small)
		undo_rotate_a(a, rotated);
	quick_sort_a(a, b, n - small, lo + small);
	quick_sort_b(a, b, small, lo);
}

/* Ordena em B os n ranks e transfere-os para A na ordem correta. */
void	quick_sort_b(t_stack *a, t_stack *b, int n, int lo)
{
	int	big;
	int	rotated;

	if (n <= 0)
		return ;
	if (n <= 3)
		return (quick_small_b(a, b, n));
	big = n - n / 2;
	rotated = split_b(a, b, big, lo + n - big);
	if (b->size > n - big)
		undo_rotate_b(b, rotated);
	quick_sort_a(a, b, big, lo + n - big);
	quick_sort_b(a, b, n - big, lo);
}

/* Atribui ranks e inicia o quick sort com B vazia. */
void	quick_sort(t_stack *a, t_stack *b)
{
	if (a->size < 2)
		return ;
	assign_indices(a);
	quick_sort_a(a, b, a->size, 0);
}
