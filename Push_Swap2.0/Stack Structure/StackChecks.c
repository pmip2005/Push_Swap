/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackChecks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-15 21:36:03 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-15 21:36:03 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StackStruct.h"

/* Verifica se os valores estao em ordem crescente do topo ao fundo. */
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

/* Procura um valor na stack e indica se o encontrou. */
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
}
