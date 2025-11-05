/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:18:05 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/05 16:36:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    push(t_stack *src, t_stack *dst)
{
    if (src->top < 0)
        return;
    if (dst->top + 1 < dst->capacity)
        dst->values[dst->top++] = src->values[src->top--];
}

void    swap(t_stack *stack)
{
    int temp_val;
    int temp_rank;

    if (stack->top < 1)
        return;
    temp_val = stack->values[stack->top];
    stack->values[stack->top] = stack->values[stack->top - 1];
    stack->values[stack->top - 1] = temp_val;
}

void    rotate(t_stack *stack)
{
	int	tmp_val;
	int	tmp_rank;
	int	i;

	if (stack->top < 1)
		return ;
	tmp_val = stack->values[stack->top];
	i = stack->top;
	while (i > 0)
	{
		stack->values[i] = stack->values[i - 1];
		i--;
	}
	stack->values[0] = tmp_val;
}

void    reverse_rotate(t_stack *stack)
{
    int temp_val;
    int temp_rank;
    int i;

    if (stack->top < 1)
        return;
    temp_val = stack->values[0];
    i = 0;
    while (i < stack->top)
    {
        stack->values[i] = stack->values[i + 1];
        i++;
    }
    stack->values[stack->top] = temp_val;
} 
