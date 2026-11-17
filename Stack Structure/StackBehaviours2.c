/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackBehaviours2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-15 21:03:56 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-15 21:03:56 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "StackStruct.h"

void	stack_push_bottom(t_stack *stack, t_node *node)
{
	node->below = NULL;
	node->above = stack->bottom;
	if (stack->bottom)
		stack->bottom->below = node;
	else
		stack->top = node;
	stack->bottom = node;
	stack->size++;
}

void	stack_clear(t_stack *stack)
{
	while (stack->size)
		free(stack_pop(stack));
}

void	stack_reverse_rotate(t_stack *stack)
{
	t_node		*temp;

	if (stack->size < 2)
		return ;
	temp = stack_pop_bottom(stack);
	stack_push(stack, temp);
}

void	stack_rotate(t_stack *stack)
{
	t_node		*temp;

	if (stack->size < 2)
		return ;
	temp = stack_pop(stack);
	stack_push_bottom(stack, temp);
}

t_node	*stack_pop_bottom(t_stack *stack)
{
	t_node	*poppednode;

	if (stack->size == 0)
		return (NULL);
	poppednode = stack->bottom;
	stack->bottom = stack->bottom->above;
	if (stack->bottom)
		stack->bottom->below = NULL;
	else
		stack->top = NULL;
	stack->size--;
	poppednode->above = NULL;
	poppednode->below = NULL;
	return (poppednode);
}
