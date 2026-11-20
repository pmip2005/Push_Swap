/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 00:54:14 by ppoco             #+#    #+#             */
/*   Updated: 2026/11/20 00:54:14 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <limits.h>
# include "../Stack Structure/StackStruct.h"

int	parse_int(const char *text, int *value);
int	append_token(t_stack *a, const char *text);
int	append_argument(t_stack *a, const char *argument);
int	parse_arguments(t_stack *a, int argc, char **argv);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char delimiter);
char	**split_whitespace(const char *text);
void	free_tokens(char **tokens);

#endif
