/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:44:57 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/05 16:44:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// Push to b by chunks 

void    free_chunk_array(t_chunk_array *chunks)
{
    if (!chunks)
        return;
    if (chunks->chunks)
        free(chunks->chunks); // CHECK WHY NOT CHUNKS[I]
    free(chunks);
}

int calculate_chunk_count(int elements)
{
    if (elements <= 3)
        return (1);
    else if (elements <= 100)
        return ((int)(sqrt(elements)));
    else if (elements <= 500)
        return ((int)(sqrt(elements) + 16));
    else 
        return ((int)(sqrt(elements) + 20));
}

void    get_non_lis_range(t_stack *a, int *min_idx, int *max_idx)
{
    int i;
    int first_found;

    *min_idx = a->capacity;
    *max_idx = -1;
    first_found = 0;
    i = 0;
    while (i <= a->top)
    {
        if (!a->in_LIS[i])
        {
            if (a->indices[i] < *min_idx)
                *min_idx = a->indices[i];
            if (a->indices[i] > *max_idx)
                *max_idx = a->indices[i];
            first_found = 1;
        }
        i++;
    }
    if (!first_found)
    {
        *min_idx = 0;
        *max_idx = 0;
    }
}

bool    is_in_chunk(int idx, t_chunk *chunk)
{
    if (idx >= chunk->min_idx && idx <= chunk->max_idx)
        return (true);
    return (false);
}

int find_corresponding_chunk(int idx, t_chunk *chunks, int chunk_count)
{
    int i;

    i =0;
    while (i < chunk_count)
    {
        if (is_in_chunk(idx, &chunks[i]))
            return (i);
        i++;
    }
    return (-1);
}

t_chunk_array   *create_chunk(t_stack *a)
{
    int min_idx;
    int max_idx;
    int current_min;
    int i;
    t_chunk_array *chunks;

    if (count_non_lis(a) == 0)
        return (NULL);
    chunks = malloc(sizeof(t_chunk_array));
    if (!chunks)
        return (NULL);
    chunks->count = calculate_chunk_count(a->not_in_lis);
    get_non_lis_range(a, &min_idx, &max_idx);
    chunks->range = max_idx - min_idx + 1;
    chunks->size = chunks->range / chunks->count;
    if (chunks->size < 1)
        chunks->size = 1;
    chunks->chunks = malloc((chunks->count) * sizeof(t_chunk));
    if (!chunks->chunks)
    {
        free(chunks);   
        return (NULL);
    }
    current_min = min_idx;
    i = 0;
    while (i < chunks->count)
    {
        chunks->chunks[i].min_idx = current_min;
        if (i == chunks->count - 1)
            chunks->chunks[i].max_idx = max_idx;
        else 
            chunks->chunks[i].max_idx = current_min + chunks->size - 1;
        chunks->chunks[i].size = chunks->chunks[i].max_idx - chunks->chunks[i].min_idx + 1;
        current_min = chunks->chunks[i].max_idx + 1;
        i++;
    }
    return (chunks);
}
