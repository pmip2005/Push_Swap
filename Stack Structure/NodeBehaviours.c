/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeBehaviours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-14 16:14:20 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-14 16:14:20 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "StackStruct.h"

t_node	*node_new(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->below = NULL;
	node->above = NULL;
	node->value = value;
	node->index = -1;
	return (node);
}
