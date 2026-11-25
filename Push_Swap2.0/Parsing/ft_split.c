/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:24:34 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/02 16:14:38 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"
#include <stdlib.h>

/* Conta palavras delimitadas e reserva o vetor de resultado. */
static char	**allocate_words(const char *str, char c)
{
	int		i;
	int		words;
	char	**out;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			words++;
		i++;
	}
	out = malloc(sizeof(char *) * (words + 1));
	return (out);
}

/* Devolve o comprimento da palavra que comeca na posicao i. */
static int	get_word_len(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i + j] != c && s[i + j])
		j++;
	return (j);
}

/* Liberta as palavras ja criadas e o vetor que as contem. */
static void	free_words(char **ptr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(ptr[i++]);
	free(ptr);
}

/* Avanca sobre delimitadores e indica se resta uma palavra. */
static int	skip_delimiters(const char *s, int *i, char c)
{
	while (s[*i] == c)
		(*i)++;
	if (s[*i] == '\0')
		return (-1);
	return (1);
}

/* Divide uma string por um delimitador e devolve um vetor terminado em NULL. */
char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**ptr;

	if (!s)
		return (NULL);
	i = 0;
	words = 0;
	ptr = allocate_words(s, c);
	if (!ptr)
		return (free_words(ptr, words), NULL);
	while (s[i])
	{
		if (skip_delimiters(s, &i, c) == -1)
			break ;
		j = get_word_len(s, c, i);
		ptr[words] = ft_substr(s, i, j);
		if (!ptr[words])
			return (free_words(ptr, words), NULL);
		words ++;
		i += j;
	}
	ptr[words] = NULL;
	return (ptr);
}
