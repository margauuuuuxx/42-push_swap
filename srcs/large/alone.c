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
