/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-17 17:04:04 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-17 17:04:04 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_H
# define SORTING_H

# include "../Operations/Operations.h"

void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	bring_to_top(t_stack *a, t_node *target);

#endif
