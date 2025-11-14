/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:28 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/14 12:37:01 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

#ifdef DEBUG_MODE
    #define DEBUG_LOG(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#else 
    #define DEBUG_LOG(fmt, ...) ((void)0)
#endif

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
    size_t  capacity;
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

// ***** chunk *****
void    free_chunk_array(t_chunk_array *chunks);
t_chunk_array   *create_chunk(t_stack *a);
void    push_chunks_to_b(t_algo *algo);
bool    is_in_chunk(int idx, t_chunk *chunk);

// ***** compress *****
void    compress(t_stack *a);
void    merge_sort(int *arr, int *temp, int left, int right);
int     binary_search(int *sorted, int size, int target);

// ***** lis *****
t_lis*  init_lis(int size);
void    free_lis(t_lis *lis);
int     lis_binary_search(int *tail, int len, int target);
void    compute_lis(t_lis *lis, int *indices, int size);
void    mark_lis_els(t_stack *a, t_lis *lis);
void    calculate_lis(t_stack *a);
int     count_non_lis(t_stack *a);
bool    is_in_lis(t_stack *a, int pos);

// ***** t_stack utils *****
bool    parse(t_stack *a, t_stack *b, int argc, char **argv);
int     init_stack(t_stack *s, int capacity);
void    free_stack(t_stack *s);

// ***** split *****
char	**ft_split(char const *s, char c);

// ***** t_stack operations *****
void    push(t_stack *s, int value);
void    pop(t_stack *s);
int top(t_stack *s);

// ***** t_stack utils *****
int init_stack(t_stack *s, int capacity);

// ***** utils *****
int     ft_atoi(const char *str);
size_t  ft_strlen(char *str);
void	output_message(char *str);
void	print_t_stack(t_stack *s);
void    copy_stack(int *cpy, t_stack *a);

