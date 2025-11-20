/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:21:52 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:09:48 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	push_element(t_stack *s, int nbr)
{
	if (s->top + 1 < s->capacity)
	{
		s->values[++s->top] = nbr;
		s->indices[s->top] = -1;
		s->in_lis[s->top] = false;
	}
}

static bool	validate_char(char c, int pos, int *count)
{
	if ((c < '0' || c > '9') && (c != '+' && c != '-'))
		return (false);
	if (*count > 1)
		return (false);
	if (c == '+' || c == '-')
	{
		if (pos != 0)
			return (false);
		(*count)++;
	}
	return (true);
}

static bool	validate_string(char *str)
{
	int	j;
	int	count;

	if (!str || str[0] == '\0')
		return (false);
	j = ft_strlen(str) - 1;
	count = 0;
	while (j >= 0)
	{
		if (!validate_char(str[j], j, &count))
			return (false);
		j--;
	}
	return (true);
}

bool	validate_all_strings(char **str, size_t len)
{
	int	i;

	if (len == 0)
		return (false);
	i = 0;
	while (i < (int)len)
	{
		if (!validate_string(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse(t_stack *a, t_stack *b, int argc, char **argv)
{
	char	**split_str;
	size_t	capacity;
	bool	is_split;
	bool	result;

	is_split = false;
	if (argc == 2)
	{
		split_str = ft_split(argv[1], ' ');
		capacity = split_len(split_str);
		is_split = true;
	}
	else
	{
		split_str = &argv[1];
		capacity = argc - 1;
	}
	if (!init_stack(a, capacity) || !init_stack(b, capacity))
		return (false);
	result = is_valid(split_str, a, capacity);
	if (is_split)
		free_split(split_str);
	return (result);
}
