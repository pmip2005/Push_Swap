/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackStruct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-14 16:02:35 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-14 16:02:35 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKSTRUCT_H
# define STACKSTRUCT_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_node
{
	int				value;
	struct s_node	*above;
	struct s_node	*below;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

void	stack_init(t_stack *stack);
void	stack_push(t_stack *stack, t_node *node);
void	stack_push_bottom(t_stack *stack, t_node *node);
t_node	*stack_pop(t_stack *stack);
t_node	*stack_pop_bottom(t_stack *stack);
void	stack_send(t_stack *source, t_stack *destination);
void	stack_swap(t_stack *stack);
void	stack_rotate(t_stack *stack);
void	stack_reverse_rotate(t_stack *stack);
void	stack_clear(t_stack *stack);
int		stack_is_sorted(t_stack *stack);
int		stack_contains(t_stack *stack, int value);

t_node	*node_new(int value);

#endif
