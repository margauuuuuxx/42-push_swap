/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:40:40 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:38:11 by marlonco         ###   ########.fr       */
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

int find_closest_chunk_elements(t_stack *a, t_chunk *chunk)
{
    int i;
    int closest_pos;
    int min_cost;
    int cost;

    closest_pos = -1;
    min_cost = a->top + 1;
    i = 0;
    while (i <= a->top)
    {
        if (!a->in_LIS[i] && is_in_chunk(a->indices[i], chunk))
        {
            if (i <= a->top / 2)
                cost = a->top - i;
            else 
                cost = i + 1;
            if (cost < min_cost)
            {
                min_cost = cost;
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
    int median;

    pushed = b->indices[b->top];
    median = (chunk->min_idx + chunk->max_idx) / 2;
    return (pushed < median);
}

void    smart_rotation_push(t_algo *algo, t_chunk *chunk)
{
    int el_idx;
    
    while (chunk_has_elements_in_a(algo->a, chunk))
    {
        el_idx = find_closest_chunk_elements(algo->a, chunk);
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

void    sort(t_algo *algo)
{
    if (algo->a->top + 1 <= 3)
        return(sort_three(algo));
    if (algo->a->top + 1 <= 5)
        return(sort_five(algo));
    push_chunks_to_b(algo);
    push_back_to_a(algo);
}