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
	/* Declare an argument index. */
	/* Start at 1: argv[0] is the program name. */
	/* While the index is less than argc: */
	/* Pass argv[index] to append_argument. */
	/* If it fails, clear the entire stack and return 0. */
	/* Otherwise, advance to the next argument. */
	/* Once every argument succeeds, return 1. */
}
