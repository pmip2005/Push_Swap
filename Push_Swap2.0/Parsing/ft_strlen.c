/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 14:19:44 by ppoco             #+#    #+#             */
/*   Updated: 2026/10/30 20:44:00 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

/* Conta os caracteres de uma string antes do terminador nulo. */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
