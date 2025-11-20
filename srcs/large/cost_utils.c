/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:32:09 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:36:43 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	calculate_cost_a(t_cost *cost, t_stack *a, int target_pos)
{
	int	cost_forward;
	int	cost_backward;

	cost_forward = a->top - target_pos;
	cost_backward = target_pos + 1;
	if (cost_forward <= cost_backward)
	{
		cost->cost_a = cost_forward;
		cost->dir_a = true;
	}
	else
	{
		cost->cost_a = cost_backward;
		cost->dir_a = false;
	}
}

void	calculate_cost_b(t_cost *cost, t_stack *b, int target_pos)
{
	int	cost_forward;
	int	cost_backward;

	(void)target_pos;
	cost_forward = b->top - cost->b_idx;
	cost_backward = cost->b_idx + 1;
	if (cost_forward <= cost_backward)
	{
		cost->cost_b = cost_forward;
		cost->dir_b = true;
	}
	else
	{
		cost->cost_b = cost_backward;
		cost->dir_b = false;
	}
}

// if dir_a == dir_b --> same direction
int	optimize_combined_cost(t_cost *cost)
{
	int	combined;
	int	remaining;

	if (cost->dir_a == cost->dir_b)
	{
		if (cost->cost_a < cost->cost_b)
			combined = cost->cost_a;
		else
			combined = cost->cost_b;
		if (cost->cost_a > cost->cost_b)
			remaining = cost->cost_a - cost->cost_b;
		else
			remaining = cost->cost_b - cost->cost_a;
		return (combined + remaining + 1);
	}
	return (cost->cost_a + cost->cost_b + 1);
}

void	wrap_around(t_stack *a, int *best_pos)
{
	int	min_val;
	int	i;

	min_val = INT_MAX;
	i = 0;
	while (i <= a->top)
	{
		if (a->indices[i] < min_val)
		{
			min_val = a->indices[i];
			*best_pos = i;
		}
		i++;
	}
}

int	find_target_pos(int b_idx, t_stack *a)
{
	int	closest_bigger;
	int	best_pos;
	int	i;

	closest_bigger = INT_MAX;
	best_pos = 0;
	i = 0;
	while (i <= a->top)
	{
		if (a->indices[i] > b_idx && a->indices[i] < closest_bigger)
		{
			closest_bigger = a->indices[i];
			best_pos = i;
		}
		i++;
	}
	if (closest_bigger == INT_MAX)
		wrap_around(a, &best_pos);
	return (best_pos);
}
