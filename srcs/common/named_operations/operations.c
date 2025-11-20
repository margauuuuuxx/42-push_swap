/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:18:05 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:06:59 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	push(t_stack *src, t_stack *dst)
{
	if (src->top < 0)
		return ;
	if (dst->top + 1 < dst->capacity)
	{
		dst->values[++dst->top] = src->values[src->top];
		dst->indices[dst->top] = src->indices[src->top];
		dst->in_lis[dst->top] = src->in_lis[src->top--];
	}
}

void	swap(t_stack *stack)
{
	int	temp_int;
	int	temp_bool;

	if (stack->top < 1)
		return ;
	temp_int = stack->values[stack->top];
	stack->values[stack->top] = stack->values[stack->top - 1];
	stack->values[stack->top - 1] = temp_int;
	temp_int = stack->indices[stack->top];
	stack->indices[stack->top] = stack->indices[stack->top - 1];
	stack->indices[stack->top - 1] = temp_int;
	temp_bool = stack->in_lis[stack->top];
	stack->in_lis[stack->top] = stack->in_lis[stack->top - 1];
	stack->in_lis[stack->top - 1] = temp_bool;
}

void	rotate(t_stack *stack)
{
	int		tmp_val;
	int		tmp_indices;
	bool	tmp_lis;
	int		i;

	if (stack->top < 1)
		return ;
	tmp_val = stack->values[stack->top];
	tmp_indices = stack->indices[stack->top];
	tmp_lis = stack->in_lis[stack->top];
	i = stack->top;
	while (i > 0)
	{
		stack->values[i] = stack->values[i - 1];
		stack->indices[i] = stack->indices[i - 1];
		stack->in_lis[i] = stack->in_lis[i - 1];
		i--;
	}
	stack->values[0] = tmp_val;
	stack->indices[0] = tmp_indices;
	stack->in_lis[0] = tmp_lis;
}

void	reverse_rotate(t_stack *stack)
{
	int		temp_val;
	int		temp_indices;
	bool	temp_lis;
	int		i;

	if (stack->top < 1)
		return ;
	temp_val = stack->values[0];
	temp_indices = stack->indices[0];
	temp_lis = stack->in_lis[0];
	i = 0;
	while (i < stack->top)
	{
		stack->values[i] = stack->values[i + 1];
		stack->indices[i] = stack->indices[i + 1];
		stack->in_lis[i] = stack->in_lis[i + 1];
		i++;
	}
	stack->values[stack->top] = temp_val;
	stack->indices[stack->top] = temp_indices;
	stack->in_lis[stack->top] = temp_lis;
}

void	rrr(t_algo *algo)
{
	reverse_rotate(algo->a);
	reverse_rotate(algo->b);
	if (write(1, "rrr\n", 4) < 0)
		return ;
}
