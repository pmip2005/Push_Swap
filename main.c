/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-19 00:32:47 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-19 00:32:47 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PushSwap.h"

static void	throw_error(void)
{
	write(2, "Error\n", 6);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	stack_init(&a);
	stack_init(&b);
	if (!parse_arguments(&a, argc, argv))
		return (throw_error(), 1);
	if (!stack_is_sorted(&a))
	{
		if (a.size == 2)
			op_ra(&a);
		if (a.size == 3)
			sort_three(&a);
		if (a.size >= 4)
			sort_five(&a, &b);
	}
	return (stack_clear(&a), stack_clear(&b), 0);
}
