/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 00:21:10 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 00:21:10 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

/* A must be initialized and empty before this call. */
/* Return 1 on success; on failure, clear A and return 0. */
/* No arguments is a successful empty input; do not print here. */
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
