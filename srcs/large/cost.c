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

#include "../includes/push_swap.h"

t_cost	calculate_move_cost(t_algo *algo, int b_idx)
{
	t_cost	cost;
	int		target_pos;

	cost.b_idx = b_idx;
	target_pos = find_target_pos(algo->b->indices[b_idx], algo->a);
	calculate_cost_b(&cost, algo->b, target_pos);
	calculate_cost_a(&cost, algo->a, target_pos);
	cost.total = optimize_combined_cost(&cost);
	return (cost);
}

t_cost	find_cheapest_move(t_algo *algo)
{
	t_cost	cheapest;
	t_cost	current;
	int		i;

	cheapest.total = INT_MAX;
	i = 0;
	while (i <= algo->b->top)
	{
		current = calculate_move_cost(algo, i);
		if (current.total < cheapest.total)
			cheapest = current;
		i++;
	}
	return (cheapest);
}

void	execute_same_dir(int *remaining_a, int *remaining_b, t_algo *algo,
		t_cost *cost)
{
	int	combined;

	combined = (*remaining_a < *remaining_b) ? *remaining_a : *remaining_b;
	while (combined > 0)
	{
		if (cost->dir_a)
			rr(algo);
		else
			rrr(algo);
		combined--;
	}
	*remaining_a -= (cost->cost_a < cost->cost_b) ? cost->cost_a : cost->cost_b;
	*remaining_b -= (cost->cost_a < cost->cost_b) ? cost->cost_a : cost->cost_b;
}

static void	execute_rotations_a(int remaining_a, t_algo *algo, bool dir_a)
{
	while (remaining_a > 0)
	{
		if (dir_a)
			ra(algo);
		else
			rra(algo);
		remaining_a--;
	}
}

static void	execute_rotations_b(int remaining_b, t_algo *algo, bool dir_b)
{
	while (remaining_b > 0)
	{
		if (dir_b)
			rb(algo);
		else
			rrb(algo);
		remaining_b--;
	}
}

void	execute_move(t_algo *algo, t_cost *cost)
{
	int	remaining_a;
	int	remaining_b;

	remaining_a = cost->cost_a;
	remaining_b = cost->cost_b;
	if (cost->dir_a == cost->dir_b)
		execute_same_dir(&remaining_a, &remaining_b, algo, cost);
	execute_rotations_a(remaining_a, algo, cost->dir_a);
	execute_rotations_b(remaining_b, algo, cost->dir_b);
	pa(algo);
}
