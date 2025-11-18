#include "../includes/push_swap.h"

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

static int	get_chunks(int size)
{
	if (size <= 100)
		return (5);
	if (size <= 500)
		return (9);
	return (20);
}

typedef struct s_push_ctx
{
	int		chunks;
	int		chunk_sz;
	int		target;
	int		pushed_count;
	int		target_push_count;
}			t_push_ctx;

static void	init_push_ctx(t_push_ctx *ctx, int size)
{
	ctx->chunks = get_chunks(size);
	ctx->chunk_sz = size / ctx->chunks;
	ctx->target = 0;
	ctx->pushed_count = 0;
	ctx->target_push_count = size - 3;
}

static int	find_best_element(t_algo *algo, t_push_ctx *ctx)
{
	int	i;
	int	pos;
	int	best_cost;
			int cost;

	best_cost = INT_MAX;
	pos = -1;
	i = 0;
	while (i <= algo->a->top)
	{
		if (!algo->a->in_lis[i] && algo->a->indices[i] >= ctx->target
			&& algo->a->indices[i] < ctx->target + ctx->chunk_sz)
		{
			cost = (algo->a->top - i < i + 1) ? algo->a->top - i : i + 1;
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

static void	rotate_b_if_needed(t_algo *algo, t_push_ctx *ctx)
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

static void	push_with_standard_chunking(t_algo *algo, int size)
{
	int	chunks;
	int	chunk_sz;
	int	target;
	int	max_to_keep;
		int i;
		int pos;
		int best_cost;
				int cost;
			int threshold;

	chunks = get_chunks(size);
	chunk_sz = size / chunks;
	target = 0;
	max_to_keep = size - 3;
	while (algo->b->top < size - 4)
	{
		best_cost = INT_MAX;
		pos = -1;
		i = 0;
		while (i <= algo->a->top)
		{
			if (algo->a->indices[i] < max_to_keep
				&& algo->a->indices[i] >= target && algo->a->indices[i] < target
				+ chunk_sz)
			{
				cost = (algo->a->top - i < i + 1) ? algo->a->top - i : i + 1;
				if (cost < best_cost)
				{
					best_cost = cost;
					pos = i;
				}
			}
			i++;
		}
		if (pos == -1)
		{
			target += chunk_sz;
			if (target >= max_to_keep)
				break ;
			continue ;
		}
		smart_rotate_to_top(algo->a, pos, algo, 'a');
		pb(algo);
		if (algo->b->top > 2)
		{
			threshold = target + (int)(chunk_sz * 0.50);
			if (algo->b->indices[algo->b->top] < threshold)
				rb(algo);
		}
	}
}

static void	sort_remaining_in_a(t_algo *algo)
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

static void	push_back_simple(t_algo *algo)
{
		int mx_p;
		int mx_v;
		int i;

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
