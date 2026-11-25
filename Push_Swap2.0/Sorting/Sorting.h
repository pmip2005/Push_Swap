/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:34:30 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/25 02:01:46 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_H
# define SORTING_H

# include "../Operations/Operations.h"

void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	chunk_sort(t_stack *a, t_stack *b);

void	bring_to_top(t_stack *s, t_node *target, char stack);
void	assign_indices(t_stack *a);
int		forward_is_cheaper(int position, int size);
t_node	*find_chunk_target(t_stack *a, int first_rank, int end_rank);
void	push_chunk(t_stack *a, t_stack *b, int first_rank, int end_rank);
void	pull_max(t_stack *a, t_stack *b);

void	quick_sort(t_stack *a, t_stack *b);
void	quick_sort_a(t_stack *a, t_stack *b, int n, int lo);
void	quick_sort_b(t_stack *a, t_stack *b, int n, int lo);
void	quick_small_a(t_stack *a, int n);
void	quick_small_b(t_stack *a, t_stack *b, int n);
int		split_a(t_stack *a, t_stack *b, int small, int pivot);
int		split_b(t_stack *a, t_stack *b, int big, int pivot);
void	undo_rotate_a(t_stack *a, int rotated);
void	undo_rotate_b(t_stack *b, int rotated);

#endif
