/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:31:35 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:08:02 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

size_t	split_len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static bool	no_duplicates(t_stack *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->top)
	{
		j = i + 1;
		while (j <= s->top)
		{
			if (s->values[i] == s->values[j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	fill_stack(char **str, t_stack *s, size_t len)
{
	int			i;
	long long	nbr;

	i = (int)len - 1;
	while (i >= 0)
	{
		nbr = ft_atoi(str[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			return (false);
		push_element(s, (int)nbr);
		i--;
	}
	return (true);
}

bool	is_valid(char **str, t_stack *s, size_t len)
{
	if (!validate_all_strings(str, len))
		return (false);
	if (!fill_stack(str, s, len))
		return (false);
	return (no_duplicates(s));
}
