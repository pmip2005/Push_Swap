/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SplitWhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 00:00:53 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 00:00:53 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

void	free_tokens(char **tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

/* Normalize a temporary copy; keep the original argument unchanged. */
char	**split_whitespace(const char *text)
{
	char	*copy;
	char	**tokens;
	size_t	i;

	if (!text)
		return (NULL);
	copy = malloc(ft_strlen(text) + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (text[i])
	{
		copy[i] = text[i];
		if (text[i] >= 9 && text[i] <= 13)
			copy[i] = ' ';
		i++;
	}
	copy[i] = '\0';
	tokens = ft_split(copy, ' ');
	free(copy);
	return (tokens);
}
