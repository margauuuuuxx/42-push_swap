/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:21:49 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 16:26:39 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    sort_medium_stack(t_algo *algo)
{
    int size;
    int mid;
    int i;
    int pos;
    int min_pos;
    int iterations;

    size = algo->a->top + 1;
    mid = size / 2;
    i = 0;
    while (i < mid)
    {
        pos = find_index_pos(algo->a, i);
        if (pos != -1)
            push_to_b_optimized(algo, pos);
        i++;
    }
    iterations = 0;
    while (!is_sorted(algo->a) && algo->a->top > 0 && iterations < size * size)
    {
        min_pos = find_min_pos(algo->a);
        
        if (min_pos == algo->a->top)
        {
            pb(algo);
            iterations = 0;
        }
        else
        {
            rotate_to_top(algo->a, min_pos, algo, 'a');
            iterations++;
        }
    }
    push_back_to_a(algo);
}