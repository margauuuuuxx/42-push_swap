/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:45:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:45:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	calculate_cost(t_algo *algo, int i)
{
	int	cost_forward;
	int	cost_backward;

	cost_forward = algo->a->top - i;
	cost_backward = i + 1;
	if (cost_forward < cost_backward)
		return (cost_forward);
	return (cost_backward);
}

static int	find_best_element(t_algo *algo, t_push_ctx *ctx)
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

static void	push_non_lis_to_b(t_algo *algo, int size)
{
	t_push_ctx	ctx;
	int			pos;

	init_push_ctx(&ctx, size);
	while (ctx.pushed_count < ctx.target_push_count && algo->a->top > 2)
	{
		pos = find_best_element(algo, &ctx);
		if (pos == -1)
		{
			ctx.target += ctx.chunk_sz;
			if (ctx.target >= size)
				break ;
			continue ;
		}
		smart_rotate_to_top(algo->a, pos, algo, 'a');
		pb(algo);
		ctx.pushed_count++;
		rotate_b_if_needed(algo, &ctx);
	}
}

static void	init_chunk_ctx(t_chunk_ctx *ctx, int size)
{
	ctx->chunks = get_chunks(size);
	ctx->chunk_sz = size / ctx->chunks;
	ctx->target = 0;
	ctx->max_to_keep = size - 3;
}

static int	find_best_in_chunk(t_algo *algo, t_chunk_ctx *ctx)
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
		if (algo->a->indices[i] < ctx->max_to_keep
			&& algo->a->indices[i] >= ctx->target
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

static void	rotate_if_threshold(t_algo *algo, t_chunk_ctx *ctx)
{
	int	threshold;

	if (algo->b->top > 2)
	{
		threshold = ctx->target + (int)(ctx->chunk_sz * 0.50);
		if (algo->b->indices[algo->b->top] < threshold)
			rb(algo);
	}
}

static void	push_with_standard_chunking(t_algo *algo, int size)
{
	t_chunk_ctx	ctx;
	int			pos;

	init_chunk_ctx(&ctx, size);
	while (algo->b->top < size - 4)
	{
		pos = find_best_in_chunk(algo, &ctx);
		if (pos == -1)
		{
			ctx.target += ctx.chunk_sz;
			if (ctx.target >= ctx.max_to_keep)
				break ;
			continue ;
		}
		smart_rotate_to_top(algo->a, pos, algo, 'a');
		pb(algo);
		rotate_if_threshold(algo, &ctx);
	}
}

static void	push_back_simple(t_algo *algo)
{
	int	mx_p;
	int	mx_v;
	int	i;

	while (algo->b->top >= 0)
	{
		mx_p = 0;
		mx_v = algo->b->indices[0];
		i = 1;
		while (i <= algo->b->top)
		{
			if (algo->b->indices[i] > mx_v)
			{
				mx_v = algo->b->indices[i];
				mx_p = i;
			}
			i++;
		}
		smart_rotate_to_top(algo->b, mx_p, algo, 'b');
		pa(algo);
	}
	final_rotate_to_min(algo);
}

void	sort_medium_stack(t_algo *algo)
{
	int	size;

	size = algo->a->top + 1;
	if (size > 100)
		push_non_lis_to_b(algo, size);
	else
		push_with_standard_chunking(algo, size);
	sort_remaining_in_a(algo);
	if (size <= 100)
		push_back_simple(algo);
	else
		push_back_to_a(algo);
}
