/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:40:40 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 16:27:52 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int init_algo(t_algo *algo, t_stack *a, t_stack *b)
{
    algo->a = a;
    algo->b = b;
    algo->chunks = create_chunk(a);
    if (!algo->chunks)
    {
        free_stack(a);
        free_stack(b);
        return (1);
    }
    return (0);
}

bool    chunk_has_elements_in_a(t_stack *a, t_chunk *chunk)
{
    int i;

    i = 0;
    while (i <= a->top)
    {
        if (!a->in_LIS[i] && is_in_chunk(a->indices[i], chunk))
            return (true);
        i++;
    }
    return (false);
}

static int calculate_b_median(t_stack *b)
{
    int sum;
    int count;
    int i;
    
    if (b->top < 0)
        return (0);
    sum = 0;
    count = 0;
    i = 0;
    while (i <= b->top)
    {
        sum += b->indices[i];
        count++;
        i++;
    }
    return (sum / count);
}

int find_closest_chunk_elements(t_stack *a, t_chunk *chunk, t_stack *b)
{
    int i;
    int closest_pos;
    int min_cost;
    int cost;
    int future_cost;
    int median_b;
    int total_cost;

    closest_pos = -1;
    min_cost = INT_MAX;
    median_b = calculate_b_median(b);
    i = 0;
    while (i <= a->top)
    {
        if (!a->in_LIS[i] && is_in_chunk(a->indices[i], chunk))
        {
            if (i <= a->top / 2)
                cost = a->top - i;
            else 
                cost = i + 1;
            future_cost = abs(a->indices[i] - median_b) / 2;
            total_cost = cost + future_cost;
            if (total_cost < min_cost)
            {
                min_cost = total_cost;
                closest_pos = i;
            }
        }
        i++;
    }
    return (closest_pos);
}

void    rotate_to_top(t_stack *s, int pos, t_algo *algo, char c)
{
    int rotation;
    
    if (pos == s->top)
        return;
    if (pos > s->top / 2)
    {
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
    else 
    {
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
}

bool    should_rotate_b(t_stack *b, t_chunk *chunk)
{
    int pushed;
    int threshold;
    int chunk_range;

    if (b->top <= 2)
        return (false);
    pushed = b->indices[b->top];
    chunk_range = chunk->max_idx - chunk->min_idx;
    threshold = chunk->min_idx + (int)(chunk_range * 0.35);
    return (pushed < threshold);
}

void    smart_rotation_push(t_algo *algo, t_chunk *chunk)
{
    int el_idx;
    
    while (chunk_has_elements_in_a(algo->a, chunk))
    {
        el_idx = find_closest_chunk_elements(algo->a, chunk, algo->b);
        if (el_idx == -1)
            break;
        rotate_to_top(algo->a, el_idx, algo, 'a');
        pb(algo);
        if (algo->b->top > 0 && should_rotate_b(algo->b, chunk))
            rb(algo);
    }
}

void    push_chunks_to_b(t_algo *algo)
{
    int i;

    if (!algo->chunks)
        return;
    i = 0;
    while (i < algo->chunks->count)
    {
        smart_rotation_push(algo, &algo->chunks->chunks[i]);
        i++;
    }
}

static int find_max_idx(t_stack *s)
{
    int max_pos;
    int max_val;
    int i;
    
    max_pos = 0;
    max_val = s->indices[0];
    i = 1;
    while (i <= s->top)
    {
        if (s->indices[i] > max_val)
        {
            max_val = s->indices[i];
            max_pos = i;
        }
        i++;
    }
    return (max_pos);
}

void sort_large_stack(t_algo *algo)
{
    int size;
    int to_push;
    int max_pos;
    
    size = algo->a->top + 1;
    
    // Push all but 3 to B
    to_push = size - 3;
    while (to_push > 0 && algo->a->top > 2)
    {
        pb(algo);
        to_push--;
    }
    
    // Sort remaining 3
    if (algo->a->top == 2)
        sort_three(algo);
    
    // Push back largest first from B
    while (algo->b->top >= 0)
    {
        max_pos = find_max_idx(algo->b);
        smart_rotate_to_top(algo->b, max_pos, algo, 'b');
        pa(algo);
    }
}

void    sort(t_algo *algo)
{
    int size;

    size = algo->a->top + 1;
    if (size == 2)
    {
        if (!is_sorted(algo->a))
            sa(algo);
        return;
    }
    if (size == 3)
    {
        sort_three(algo);
        return;
    }
    if (size <= 5)
    {
        sort_five(algo);
        return;
    }
    if (size <= 20)
    {
        sort_small_stack(algo);
        return;
    }
    sort_medium_stack(algo);
}