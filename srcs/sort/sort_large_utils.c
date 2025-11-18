#include "../../includes/push_swap.h"

int	get_chunks(int size)
{
	if (size <= 100)
		return (5);
	if (size <= 500)
		return (9);
	return (20);
}

void	init_push_ctx(t_push_ctx *ctx, int size)
{
	ctx->chunks = get_chunks(size);
	ctx->chunk_sz = size / ctx->chunks;
	ctx->target = 0;
	ctx->pushed_count = 0;
	ctx->target_push_count = size - 3;
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

void	smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c)
{
	int	cf;
	int	cb;

	cf = s->top - pos;
	cb = pos + 1;
	if (pos == s->top)
		return ;
	if (cf <= cb)
		while (cf-- > 0)
			(c == 'a') ? ra(algo) : rb(algo);
	else
		while (cb-- > 0)
			(c == 'a') ? rra(algo) : rrb(algo);
}
