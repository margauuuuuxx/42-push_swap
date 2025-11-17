/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:03:56 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 16:03:06 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

bool    is_sorted(t_stack *s)
{
    int i;

    i = 0;
    while (i < s->top)
    {
        if (s->values[i] < s->values[i + 1])
            return (false);
        i++;
    }
    return (true);
}

void    sort_three(t_algo *algo)
{
    t_stack *a;
    int     top;
    int     mid;
    int     bottom;

    a = algo->a;
    if (is_sorted(a))
        return;
    top = a->values[a->top];
    mid = a->values[a->top - 1];
    bottom = a->values[0];
    if (top > mid && mid < bottom && top < bottom)
        sa(algo);
    else if (top > mid && mid > bottom)
    {
        sa(algo);
        rra(algo);
    }
    else if (top > mid && mid < bottom && top > bottom)
        ra(algo);
    else if (top < mid && mid > bottom && top < bottom)
    {
        sa(algo);
        ra(algo);
    }
    else if (top < mid && mid > bottom && top > bottom)
        rra(algo);
}

void    sort_five(t_algo *algo)
{
    int min_pos;

    if (is_sorted(algo->a))
        return;
    while (algo->b->top < 1)
    {
        min_pos = find_min_pos(algo->a);
        rotate_to_top(algo->a, min_pos, algo, 'a');
        pb(algo);
    }
    sort_three(algo);
    pa(algo);
    pa(algo);
    if (algo->b->top >= 0 && algo->b->values[algo->b->top] < algo->b->values[algo->b->top - 1])
        sb(algo);
}
