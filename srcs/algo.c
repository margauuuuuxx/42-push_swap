/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:40:40 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/05 16:14:00 by marlonco         ###   ########.fr       */
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
    algo->pos_tree = NULL; // COMPLETE
    return (0);
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
    
    while (chunk_has_elements_in_a(algo->a, chunk)) // IMPLEMENT
    {
        el_idx = find_closest_chunk_element(algo->a, chunk); // IMPLEMENT
        rotate_to_top(algo->a, el_idx, "a"); // IMPLEMENT 
        pb(algo);
        if (should_rotate_b(algo->b, chunk)) // IMPLEMENT
            rb(algo);
    }
}

void    push_chunks_to_b(t_algo *algo)
{
    int i;
    int j;

    if (!algo->chunks)
        return;
    i = 0;
    while (i < algo->chunks->count)
    {
        j = 0;
        while (j <= algo->a->top)
        {
               if (!algo->a->in_LIS[j] && is_in_chunk(algo->a->indices[j], &algo->chunks->chunks[i]))
               {
                // ROATATE TO TOP AND PUSH TO B
               }
            j++;
        }
        i++;
    }
}

void    sort(t_algo *algo)
{
    push_chunks_to_b(algo);
}