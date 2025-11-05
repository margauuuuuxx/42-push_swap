/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:18:05 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/05 16:18:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    push(t_stack *src, t_stack *dst)
{
    if (src->top < 0)
        return;
    dst->top++;
    dst->values[dst->top] = src->values[src->top];
    dst->ranks[dst->top] = src->ranks[src->top];
    src->top--;
}

void    swap(t_stack *stack)
{
    int temp_val;
    int temp_rank;

    if (stack->top < 1)
        return;
    temp_val = stack->values[stack->top];
    temp_rank = stack->ranks[stack->top];
    stack->values[stack->top] = stack->values[stack->top - 1];
    stack->ranks[stack->top] = stack->ranks[stack->top - 1];
    stack->values[stack->top - 1] = temp_val;
    stack->ranks[stack->top - 1] = temp_rank;
}

void    rotate(t_stack *stack)
{
	int	tmp_val;
	int	tmp_rank;
	int	i;

	if (stack->top < 1)
		return ;
	tmp_val = stack->values[stack->top];
	tmp_rank = stack->ranks[stack->top];
	i = stack->top;
	while (i > 0)
	{
		stack->values[i] = stack->values[i - 1];
		stack->ranks[i] = stack->ranks[i - 1];
		i--;
	}
	stack->values[0] = tmp_val;
	stack->ranks[0] = tmp_rank;
}

void    reverse_rotate(t_stack *stack)
{
    int temp_val;
    int temp_rank;
    int i;

    if (stack->top < 1)
        return;
    temp_val = stack->values[0];
    temp_rank = stack->ranks[0];
    i = 0;
    while (i < stack->top)
    {
        stack->values[i] = stack->values[i + 1];
        stack->ranks[i] = stack->ranks[i + 1];
        i++;
    }
    stack->values[stack->top] = temp_val;
    stack->ranks[stack->top] = temp_rank;
} 