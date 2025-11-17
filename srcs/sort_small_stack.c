/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:08:11 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 16:27:31 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int find_index_pos(t_stack *s, int target_idx)
{
    int i;
    
    i = 0;
    while (i <= s->top)
    {
        if (s->indices[i] == target_idx)
            return (i);
        i++;
    }
    return (-1);
}

void    push_to_b_optimized(t_algo *algo, int pos)
{
    int cost_forward;
    int cost_backward;

    if (pos == algo->a->top)
        return(pb(algo));
    cost_forward = algo->a->top - pos;
    cost_backward = pos + 1;
    if (cost_forward <= cost_backward)
    {
        while (cost_forward-- > 0)
            ra(algo);
    }
    else
    {
        while (cost_backward-- > 0)
            rra(algo);
    }
    pb(algo);
}

void    sort_small_stack(t_algo *algo)
{
    int size;
    int push_count;
    int i;
    int pos;
    int iterations;
    int max_iter;
    
    size = algo->a->top + 1;
    push_count = size / 3;
    if (push_count < 2)
        push_count = 2;
    i = 0;
    while (i < push_count && algo->a->top > 2)
    {
        pos = find_index_pos(algo->a, i);
        if (pos != -1)
            push_to_b_optimized(algo, pos);
        i++;
    }
    if (algo->a->top == 2)
    {
        sort_three(algo);
    }
    else if (algo->a->top > 2)
    {
        iterations = 0;
        max_iter = (algo->a->top + 1) * (algo->a->top + 1);
        while (!is_sorted(algo->a) && iterations < max_iter)
        {
            if (algo->a->indices[algo->a->top] > algo->a->indices[algo->a->top - 1])
                sa(algo);
            ra(algo);
            iterations++;
        }
        final_rotate_to_min(algo);
    }
    while (algo->b->top >= 0)
        pa(algo);
}