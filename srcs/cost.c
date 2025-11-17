/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:32:09 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:36:43 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"


void    calculate_cost_a(t_cost *cost, t_stack *a, int target_pos)
{
    int cost_forward;
    int cost_backward;
    
    cost_forward = a->top - target_pos;
    cost_backward = target_pos + 1;
    if (cost_forward <= cost_backward)
    {
        cost->cost_a = cost_forward;
        cost->dir_a = true;
    }
    else 
    {
        cost->cost_a = cost_backward;
        cost->dir_a = false;
    }
}

void    calculate_cost_b(t_cost *cost, t_stack *b, int target_pos)
{
    int cost_forward;
    int cost_backward;
    (void)target_pos;
    
    cost_forward = b->top - cost->b_idx;
    cost_backward = cost->b_idx + 1;
    if (cost_forward <= cost_backward)
    {
        cost->cost_b = cost_forward;
        cost->dir_b = true;
    }
    else
    {
        cost->cost_b = cost_backward;
        cost->dir_b = false;
    }
}

int optimize_combined_cost(t_cost *cost)
{
    int combined;
    int remaining;

    if (cost->dir_a == cost->dir_b) // same direction
    {
        combined = (cost->cost_a < cost->cost_b) ? cost->cost_a : cost->cost_b;
        remaining = (cost->cost_a > cost->cost_b) ? (cost->cost_a - cost->cost_b) : (cost->cost_b - cost->cost_a);
        return (combined + remaining + 1);
    }
    return (cost->cost_a + cost->cost_b + 1);
}

void    wrap_around(t_stack *a, int *best_pos)
{
    int min_val;
    int i;

    min_val = INT_MAX;
    i = 0;
    while (i <= a->top)
    {
        if (a->indices[i] < min_val)
        {
            min_val = a->indices[i];
            *best_pos = i;
        }
        i++;
    }
}

int find_target_pos(int b_idx, t_stack *a)
{
    int closest_bigger;
    int best_pos;
    int i;

    closest_bigger = INT_MAX;
    best_pos = 0;
    i = 0;
    while (i <= a->top)
    {
        if (a->indices[i] > b_idx && a->indices[i] < closest_bigger)
        {
            closest_bigger = a->indices[i];
            best_pos = i;
        }
        i++;
    }
    if (closest_bigger == INT_MAX)
        wrap_around(a, &best_pos);
    return (best_pos);
}

t_cost  calculate_move_cost(t_algo *algo, int b_idx)
{
    t_cost              cost;
    int                 target_pos;

    cost.b_idx = b_idx;
    target_pos = find_target_pos(algo->b->indices[b_idx], algo->a);
    calculate_cost_b(&cost, algo->b, target_pos);
    calculate_cost_a(&cost, algo->a, target_pos);
    cost.total = optimize_combined_cost(&cost);
    return (cost);
}

t_cost  find_cheapest_move(t_algo *algo)
{
    t_cost  cheapest;
    t_cost  current;
    int     i;

    cheapest.total = INT16_MAX;
    i = 0;
    while (i <= algo->b->top)
    {
        current = calculate_move_cost(algo, i);
        if (current.total < cheapest.total)
            cheapest = current;
        i++;
    }
    return (cheapest);
}

void    execute_same_dir(int *remaining_a, int *remaining_b, t_algo *algo, t_cost *cost)
{
    int combined;

    combined = (*remaining_a < *remaining_b) ? *remaining_a : *remaining_b;
    while (combined > 0)
    {
        if (cost->dir_a)
            rr(algo);
        else
            rrr(algo);
        combined--;
    }
    *remaining_a -= (cost->cost_a < cost->cost_b) ? cost->cost_a : cost->cost_b;
    *remaining_b -= (cost->cost_a < cost->cost_b) ? cost->cost_a : cost->cost_b;
}

void    execute_move(t_algo *algo, t_cost *cost)
{
    int remaining_a;
    int remaining_b;

    remaining_a = cost->cost_a;
    remaining_b = cost->cost_b;
    if (cost->dir_a == cost->dir_b)
        execute_same_dir(&remaining_a, &remaining_b, algo, cost);
    while (remaining_a > 0)
    {
        if (cost->dir_a)
            ra(algo);
        else 
        rra(algo);
        remaining_a--;
    }
    while (remaining_b > 0)
    {
        if (cost->dir_b)
            rb(algo);
        else 
        rrb(algo);
        remaining_b--;
    }
    pa(algo);
}

