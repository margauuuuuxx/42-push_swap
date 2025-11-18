/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:08:11 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 16:27:31 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_index_pos(t_stack *s, int target_idx)
{
	int	i;

	i = 0;
	while (i <= s->top)
	{
		if (s->indices[i] == target_idx)
			return (i);
		i++;
	}
	return (-1);
}

void	push_to_b_optimized(t_algo *algo, int pos)
{
	int	cost_forward;
	int	cost_backward;

	if (pos == algo->a->top)
		return (pb(algo));
	cost_forward = algo->a->top - pos;
	cost_backward = pos + 1;
	if (cost_forward <= cost_backward)
	{
		while (cost_forward-- > 0)
			ra(algo);
	}
	else
	{
		while (cost_backward-- > 0)
			rra(algo);
	}
	pb(algo);
}

static void	simple_sort_remaining(t_algo *algo)
{
	int	min_pos;
	int	size;
	int	i;

	size = algo->a->top + 1;
	i = 0;
	while (algo->a->top > 2 && i < size)
	{
		min_pos = find_min_pos(algo->a);
		rotate_to_top(algo->a, min_pos, algo, 'a');
		pb(algo);
		i++;
	}
	if (algo->a->top == 2)
		sort_three(algo);
}

void	sort_small_stack(t_algo *algo)
{
	int	size;
	int	i;
	int	pos;

	size = algo->a->top + 1;
	if (size > 5)
	{
		i = 0;
		while (i < 2 && algo->a->top > 3)
		{
			pos = find_index_pos(algo->a, i);
			if (pos != -1)
				push_to_b_optimized(algo, pos);
			i++;
		}
	}
	simple_sort_remaining(algo);
	while (algo->b->top >= 0)
		pa(algo);
}
