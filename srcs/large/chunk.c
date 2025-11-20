/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:44:57 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 13:54:32 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_chunk_array(t_chunk_array *chunks)
{
	if (!chunks)
		return ;
	if (chunks->chunks)
		free(chunks->chunks);
	free(chunks);
}

int	calculate_chunk_count(int elements)
{
	int	optimal_chunks;
	int	root;

	if (elements <= 3)
		return (1);
	root = int_sqrt(elements);
	optimal_chunks = (int)(root * 1.2);
	if (optimal_chunks < 3)
		optimal_chunks = 3;
	return (optimal_chunks);
}

static void	init_chunk_array(t_chunk_array *chunks, int min_idx, int max_idx)
{
	chunks->range = max_idx - min_idx + 1;
	chunks->size = chunks->range / chunks->count;
	if (chunks->size < 1)
		chunks->size = 1;
}

static void	fill_chunks(t_chunk_array *chunks, int min_idx, int max_idx)
{
	int	current_min;
	int	i;

	current_min = min_idx;
	i = 0;
	while (i < chunks->count)
	{
		chunks->chunks[i].min_idx = current_min;
		if (i == chunks->count - 1)
			chunks->chunks[i].max_idx = max_idx;
		else
			chunks->chunks[i].max_idx = current_min + chunks->size - 1;
		chunks->chunks[i].size = chunks->chunks[i].max_idx
			- chunks->chunks[i].min_idx + 1;
		current_min = chunks->chunks[i].max_idx + 1;
		i++;
	}
}

t_chunk_array	*create_chunk(t_stack *a)
{
	int				min_idx;
	int				max_idx;
	t_chunk_array	*chunks;

	if (a->not_in_lis == 0)
		return (NULL);
	chunks = malloc(sizeof(t_chunk_array));
	if (!chunks)
		return (NULL);
	chunks->count = calculate_chunk_count(a->not_in_lis);
	get_non_lis_range(a, &min_idx, &max_idx);
	init_chunk_array(chunks, min_idx, max_idx);
	chunks->chunks = malloc((chunks->count) * sizeof(t_chunk));
	if (!chunks->chunks)
	{
		free(chunks);
		return (NULL);
	}
	fill_chunks(chunks, min_idx, max_idx);
	return (chunks);
}
