/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackChecks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-15 21:36:03 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-15 21:36:03 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StackStruct.h"

int	stack_is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	if (stack->size <= 1)
		return (1);
	while (current->below)
	{
		if (current->value > current->below->value)
			return (0);
		current = current->below;
	}
	return (1);
}

int	stack_contains(t_stack *stack, int value)
{
	t_node	*current;

	if (!stack->size)
		return (0);
	current = stack->top;
	while (current)
	{
		if (current->value == value)
			return (1);
		current = current->below;
	}
	return (0);
	/* Declare a node pointer for traversal. */
	/* Start at the top of the stack. */
	/* While the current node exists: */
	/* If its value matches the requested value, return 1. */
	/* Otherwise, move to the node below. */
	/* If no match was found, return 0. */
}
