/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:10:44 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:11:07 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	char	**str;
}	t_split;

typedef struct s_t_stack {
    int     *values;
    int     *indices; // normalized indices
    bool    *in_LIS;
    int     not_in_lis;
    int     top;
    int     capacity;
}   t_stack;

typedef struct s_cost {
    int     cost_a; // rotations to get a on top
    int     cost_b; // rotations to get b on top
    bool    dir_a;
    bool    dir_b;
    int     total; // total operations needed to push b to target a
    int     b_idx; // which el of b 
}   t_cost;

// position trackr for BST node
typedef struct s_node_pos {
    int                 idx; //normalized idx
    int                 stack_pos; // position in the stack
    struct s_node_pos   *left;
    struct s_node_pos   *right;
}   t_node_pos;

typedef struct s_chunk {
    int min_idx; // min idx in chunk
    int max_idx; // max idx in chunk
    int size;
}   t_chunk;

typedef struct s_chunk_array {
    t_chunk *chunks;
    int     count;
    int     size;
    int     range;
}   t_chunk_array;

typedef struct s_lis {
    int *lens; // lens of LIS ending at i
    int *prev; // previous els in LIS
    int *tail; // smallest tail for each len
    int max_len; // max LIS len 
}   t_lis;

typedef struct s_algo {
    t_stack         *a;
    t_stack         *b;
    t_node_pos      *pos_tree;
    t_chunk_array   *chunks;
}   t_algo;

typedef struct s_merge {
    int left;
    int right;
    int mid;
}   t_merge;