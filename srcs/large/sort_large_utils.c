/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:45:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:45:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	init_chunk_ctx(t_chunk_ctx *ctx, int size)
{
	ctx->chunks = get_chunks(size);
	ctx->chunk_sz = size / ctx->chunks;
	ctx->target = 0;
	ctx->max_to_keep = size - 3;
}

void	init_push_ctx(t_push_ctx *ctx, int size)
{
	ctx->chunks = get_chunks(size);
	ctx->chunk_sz = size / ctx->chunks;
	ctx->target = 0;
	ctx->pushed_count = 0;
	ctx->target_push_count = size - 3;
}

int	get_chunks(int size)
{
	if (size <= 100)
		return (5);
	if (size <= 500)
		return (9);
	return (20);
}

void	sort_remaining_in_a(t_algo *algo)
{
	if (algo->a->top == 2)
		sort_three(algo);
	else if (algo->a->top > 2)
	{
		while (algo->a->top > 2)
			pb(algo);
		if (algo->a->top == 2)
			sort_three(algo);
	}
}

void	rotate_b_if_needed(t_algo *algo, t_push_ctx *ctx)
{
	int	pushed_idx;
	int	threshold;

	if (algo->b->top > 2)
	{
		pushed_idx = algo->b->indices[algo->b->top];
		threshold = ctx->target + (int)(ctx->chunk_sz * 0.50);
		if (pushed_idx < threshold)
			rb(algo);
	}
}
