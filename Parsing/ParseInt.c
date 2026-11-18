/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseInt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-18 22:29:50 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-18 22:29:50 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

/* Check the next step before multiplying, so even huge tokens are safe. */
static int	parse_magnitude(const char *text, long long limit, long long *acc)
{
	int	digit;

	*acc = 0;
	if (!*text)
		return (0);
	while (*text)
	{
		if (*text < '0' || *text > '9')
			return (0);
		digit = *text - '0';
		if (*acc > (limit - digit) / 10)
			return (0);
		*acc = *acc * 10 + digit;
		text++;
	}
	return (1);
}

/* Parse one integer token, without surrounding whitespace. */
/* Return 1 on success, 0 on error; change *value only on success. */
int	parse_int(const char *text, int *value)
{
	int			sign;
	long long	limit;
	long long	acc;

	if (!text || !value)
		return (0);
	sign = 1;
	if (*text == '-' || *text == '+')
	{
		if (*text == '-')
			sign = -1;
		text++;
	}
	limit = INT_MAX;
	if (sign == -1)
		limit = -(long long)INT_MIN;
	if (!parse_magnitude(text, limit, &acc))
		return (0);
	*value = (int)(acc * sign);
	return (1);
}
