/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:40:40 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:11:56 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	init_algo(t_algo *algo, t_stack *a, t_stack *b)
{
	algo->a = a;
	algo->b = b;
	algo->chunks = create_chunk(a);
	if (!algo->chunks)
	{
		free_both_stacks(a, b);
		return (1);
	}
	return (0);
}

static void	case1_rotation(t_stack *s, int pos, t_algo *algo, char c)
{
	int	rotation;

	rotation = s->top - pos;
	while (rotation > 0)
	{
		if (c == 'a')
			ra(algo);
		else
			rb(algo);
		rotation--;
	}
}

static void	case2_rotation(int pos, t_algo *algo, char c)
{
	int	rotation;

	rotation = pos + 1;
	while (rotation > 0)
	{
		if (c == 'a')
			rra(algo);
		else
			rrb(algo);
		rotation--;
	}
}

void	rotate_to_top(t_stack *s, int pos, t_algo *algo, char c)
{
	if (pos == s->top)
		return ;
	if (pos > s->top / 2)
		case1_rotation(s, pos, algo, c);
	else
		case2_rotation(pos, algo, c);
}

void	sort(t_algo *algo)
{
	int	size;

	size = algo->a->top + 1;
	if (size == 2)
	{
		if (!is_sorted(algo->a))
			sa(algo);
		return ;
	}
	if (size == 3)
	{
		sort_three(algo);
		return ;
	}
	if (size <= 20)
	{
		sort_medium_stack(algo);
		return ;
	}
	sort_large_stack(algo);
}
