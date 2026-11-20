/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AppendArgument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-18 23:57:45 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-18 23:57:45 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

/* Split one argument on whitespace and append each token in order. */
/* Return 1 on success, 0 on failure, including an empty argument. */
/* On failure, earlier tokens may already be in A; the caller clears A. */
int	append_argument(t_stack *a, const char *argument)
{
	char	**token_stream;
	int		i;

	token_stream = split_whitespace(argument);
	if (!token_stream)
		return (0);
	if (token_stream[0] == NULL)
		return (free_tokens(token_stream), 0);
	i = 0;
	while (token_stream[i])
	{
		if (!append_token(a, token_stream[i]))
			return (free_tokens(token_stream), 0);
		i++;
	}
	return (free_tokens(token_stream), 1);
}
