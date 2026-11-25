/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 01:20:41 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorting.h"

/* Calcula uma largura de chunk proporcional a raiz do tamanho da stack. */
static int	chunk_width(int size)
{
	int	root;

	root = 1;
	while ((long long)root * root < size)
		root++;
	return (root * 2);
}

/* Ordena A por janelas de ranks e recupera depois os elementos de B. */
void	chunk_sort(t_stack *a, t_stack *b)
{
	int	width;
	int	first_rank;
	int	end_rank;

	width = chunk_width(a->size);
	assign_indices(a);
	first_rank = 0;
	while (a->size)
	{
		end_rank = first_rank + a->size;
		if (width < a->size)
			end_rank = first_rank + width;
		push_chunk(a, b, first_rank, end_rank);
		first_rank = end_rank;
	}
	while (b->size)
		pull_max(a, b);
}
