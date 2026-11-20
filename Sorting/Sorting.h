/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-17 17:04:04 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-17 17:04:04 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_H
# define SORTING_H

# include "../Operations/Operations.h"

void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	chunk_sort(t_stack *a, t_stack *b);

/* B must start empty; radix_sort assigns the ranks before sorting. */
void	radix_sort(t_stack *a, t_stack *b);

void	bring_to_top(t_stack *s, t_node *target, char stack);
void	assign_indices(t_stack *a);
int		forward_is_cheaper(int position, int size);
t_node	*find_chunk_target(t_stack *a, int first_rank, int end_rank);
void	push_chunk(t_stack *a, t_stack *b, int first_rank, int end_rank);
void	pull_max(t_stack *a, t_stack *b);

#endif
