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

#include "../includes/push_swap.h"

/*
	The goal is to find elements already in correct relative order
		--> referring to *indices NOT *values of stack
*/

void	compute_lis(t_lis *lis, int *indices, int size)
{
	int	len;
	int	pos;
	int	i;
	int	stack_pos;

	len = 0;
	i = 0;
	while (i < size)
	{
		stack_pos = size - 1 - i;
		pos = lis_binary_search(lis->tail, len, indices[stack_pos]);
		lis->tail[pos] = indices[stack_pos];
		lis->lens[stack_pos] = pos + 1;
		if (pos > 0)
			lis->prev[stack_pos] = lis->tail[pos - 1];
		else
			lis->prev[stack_pos] = -1;
		if (pos == len)
			len++;
		i++;
	}
	lis->max_len = len;
}

static int	find_lis_end(t_stack *a, t_lis *lis)
{
	int	max_idx;
	int	i;

	max_idx = -1;
	i = 0;
	while (i <= a->top)
	{
		if (lis->lens[i] == lis->max_len)
		{
			max_idx = i;
			break ;
		}
		i++;
	}
	return (max_idx);
}

static void	backtrack_lis(t_stack *a, t_lis *lis, int max_idx)
{
	int	current_val;
	int	i;

	current_val = lis->prev[max_idx];
	if (current_val == -1)
		return ;
	i = max_idx - 1;
	while (i >= 0)
	{
		if (a->indices[i] == current_val)
		{
			a->in_lis[i] = true;
			if (lis->prev[i] != -1)
				current_val = lis->prev[i];
			else
				break ;
		}
		i--;
	}
}

void	mark_lis_els(t_stack *a, t_lis *lis)
{
	int	max_idx;

	max_idx = find_lis_end(a, lis);
	if (max_idx == -1)
		return ;
	a->in_lis[max_idx] = true;
	backtrack_lis(a, lis, max_idx);
}

void	calculate_lis(t_stack *a)
{
	t_lis	*lis;

	lis = init_lis(a->top + 1);
	compute_lis(lis, a->indices, a->top + 1);
	mark_lis_els(a, lis);
	count_non_lis(a);
	free_lis(lis);
}
