/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeBehaviours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
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
	return (node);
}
