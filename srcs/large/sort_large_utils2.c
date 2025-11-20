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

static void	rotate_forward(t_algo *algo, char c, int count)
{
	while (count-- > 0)
	{
		if (c == 'a')
			ra(algo);
		else
			rb(algo);
	}
}

static void	rotate_backward(t_algo *algo, char c, int count)
{
	while (count-- > 0)
	{
		if (c == 'a')
			rra(algo);
		else
			rrb(algo);
	}
}

void	smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c)
{
	int	cf;
	int	cb;

	cf = s->top - pos;
	cb = pos + 1;
	if (pos == s->top)
		return ;
	if (cf <= cb)
		rotate_forward(algo, c, cf);
	else
		rotate_backward(algo, c, cb);
}

int	calculate_cost(t_algo *algo, int i)
{
	int	cost_forward;
	int	cost_backward;

	cost_forward = algo->a->top - i;
	cost_backward = i + 1;
	if (cost_forward < cost_backward)
		return (cost_forward);
	return (cost_backward);
}

int	find_best_element(t_algo *algo, t_push_ctx *ctx)
{
	int	i;
	int	pos;
	int	best_cost;
	int	cost;

	best_cost = INT_MAX;
	pos = -1;
	i = 0;
	while (i <= algo->a->top)
	{
		if (!algo->a->in_lis[i] && algo->a->indices[i] >= ctx->target
			&& algo->a->indices[i] < ctx->target + ctx->chunk_sz)
		{
			cost = calculate_cost(algo, i);
			if (cost < best_cost)
			{
				best_cost = cost;
				pos = i;
			}
		}
		i++;
	}
	return (pos);
}
