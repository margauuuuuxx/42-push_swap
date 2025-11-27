/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stack_utils.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:57:48 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/24 14:18:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	free_stack(t_stack *s)
{
	if (s->values)
		free(s->values);
	if (s->indices)
		free(s->indices);
	if (s->in_lis)
		free(s->in_lis);
}

void	free_both_stacks(t_stack *a, t_stack *b)
{
	free_stack(a);
	free_stack(b);
}

int	init_stack(t_stack *s, int capacity)
{
	int	i;

	i = 0;
	s->values = malloc(sizeof(int) * capacity);
	s->indices = malloc(sizeof(int) * capacity);
	s->in_lis = malloc(sizeof(bool) * capacity);
	if (!s->values || !s->indices || !s->in_lis)
		return (0);
	while (i < capacity)
	{
		s->in_lis[i] = false;
		i++;
	}
	s->top = -1;
	s->capacity = capacity;
	s->not_in_lis = -1;
	return (1);
}
