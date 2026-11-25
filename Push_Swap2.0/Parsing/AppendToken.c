/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AppendToken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-18 23:08:33 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-18 23:08:33 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

/* Valida um token e adiciona o respetivo valor ao fundo de A. */
int	append_token(t_stack *a, const char *text)
{
	int		parsed_value;
	t_node	*to_append;

	if (!parse_int(text, &parsed_value))
		return (0);
	if (stack_contains(a, parsed_value))
		return (0);
	to_append = node_new(parsed_value);
	if (!to_append)
		return (0);
	stack_push_bottom(a, to_append);
	return (1);
}
