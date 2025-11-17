/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:16:04 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 14:44:29 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int find_min_pos(t_stack *a)
{
    int min_pos;
    int min_val;
    int i;

    min_pos = 0;
    min_val = a->values[0];
    i = 1;
    while (i <= a->top)
    {
        if (a->values[i] < min_val)
        {
            min_val = a->values[i];
            min_pos = i;
        }
        i++;
    }
    return (min_pos);
}

void    final_rotate_to_min(t_algo *algo)
{
    int min_pos;
    int cost_forward;
    int cost_backward;

    if (is_sorted(algo->a))
        return;
    min_pos = find_min_pos(algo->a);
    cost_forward = algo->a->top - min_pos;
    cost_backward = min_pos - 1;
    if (cost_forward <= cost_backward)
    {
        while (cost_forward > 0)
        {
            ra(algo);
            cost_forward--;
        }
    }
    else
    {
        while (cost_backward > 0)
        {
            rra(algo);
            cost_backward--;
        }
    }
}
