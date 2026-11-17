/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackBehaviours.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-14 16:09:19 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-14 16:09:19 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "StackStruct.h"

void	stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

void	stack_push(t_stack *stack, t_node *node)
{
	node->below = stack->top;
	node->above = NULL;
	if (stack->top)
		stack->top->above = node;
	else
		stack->bottom = node;
	stack->top = node;
	stack->size++;
}

t_node	*stack_pop(t_stack *stack)
{
	t_node	*poppednode;

	if (stack->size == 0)
		return (NULL);
	poppednode = stack->top;
	stack->top = stack->top->below;
	if (stack->top)
		stack->top->above = NULL;
	else
		stack->bottom = NULL;
	stack->size--;
	poppednode->above = NULL;
	poppednode->below = NULL;
	return (poppednode);
}

void	stack_send(t_stack *source, t_stack *destination)
{
	t_node	*to_send;

	to_send = stack_pop(source);
	if (!to_send)
		return ;
	stack_push(destination, to_send);
}

void	stack_swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack->size < 2)
		return ;
	first = stack_pop(stack);
	second = stack_pop(stack);
	stack_push(stack, first);
	stack_push(stack, second);
}
