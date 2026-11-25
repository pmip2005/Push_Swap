/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyFlag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debento <debento@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 02:17:22 by debento           #+#    #+#             */
/*   Updated: 2026/11/25 02:17:22 by debento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PushSwap.h"

/* Compara duas strings completas sem depender de bibliotecas externas. */
static int	same_word(const char *left, const char *right)
{
	while (*left && *left == *right)
	{
		left++;
		right++;
	}
	return (*left == *right);
}

/* Traduz uma opcao reconhecida para a estrategia correspondente. */
static int	strategy_value(const char *flag)
{
	if (same_word(flag, "--simple"))
		return (SIMPLE);
	if (same_word(flag, "--medium"))
		return (MEDIUM);
	if (same_word(flag, "--complex"))
		return (COMPLEX);
	if (same_word(flag, "--adaptive"))
		return (ADAPTIVE);
	return (-1);
}

/* Retira dos argumentos a opcao de estrategia, se existir e for valida. */
t_strategy	read_strategy(int *argc, char ***argv)
{
	int	value;

	if (*argc < 2 || (*argv)[1][0] != '-' || (*argv)[1][1] != '-')
		return (ADAPTIVE);
	value = strategy_value((*argv)[1]);
	if (value < 0)
		return (ADAPTIVE);
	(*argc)--;
	(*argv)++;
	return ((t_strategy)value);
}
