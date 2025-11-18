/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:10:44 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:32:26 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdbool.h>

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	char	**str;
}	t_split;

typedef struct s_t_stack
{
	int		*values;
	int		*indices;
	bool	*in_lis;
	int		not_in_lis;
	int		top;
	int		capacity;
}	t_stack;

// costs a/b = rotations to get a/b on top
typedef struct s_cost
{
	int		cost_a;
	int		cost_b;
	bool	dir_a;
	bool	dir_b;
	int		total;
	int		b_idx;
}					t_cost;

// min/max = idx in the chunk
typedef struct s_chunk
{
	int	min_idx;
	int	max_idx;
	int	size;
}	t_chunk;

typedef struct s_chunk_array
{
	t_chunk	*chunks;
	int		count;
	int		size;
	int		range;
}	t_chunk_array;

// lens = lens of LIS ending at i
// tail = smallest tail for each len
typedef struct s_lis
{
	int	*lens;
	int	*prev;
	int	*tail;
	int	max_len;
}	t_lis;

typedef struct s_algo
{
	t_stack			*a;
	t_stack			*b;
	t_chunk_array	*chunks;
}	t_algo;

typedef struct s_merge
{
	int				left;
	int				right;
	int				mid;
}	t_merge;

typedef struct s_push_ctx
{
	int		chunks;
	int		chunk_sz;
	int		target;
	int		pushed_count;
	int		target_push_count;
}			t_push_ctx;
