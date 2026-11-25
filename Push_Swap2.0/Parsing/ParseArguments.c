/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 00:21:10 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 00:21:10 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

/* Adiciona os argumentos a A e limpa a stack se algum deles for invalido. */
int	parse_arguments(t_stack *a, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!append_argument(a, argv[i]))
			return (stack_clear(a), 0);
		i++;
	}
	return (1);
}
