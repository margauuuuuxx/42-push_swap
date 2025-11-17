/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:28 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:04:10 by marlonco         ###   ########.fr       */
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

// ***** algo *****
int     init_algo(t_algo *algo, t_stack *a, t_stack *b);
void    rotate_to_top(t_stack *s, int pos, t_algo *algo, char c);
void    sort(t_algo *algo);

// ***** chunk *****
void    free_chunk_array(t_chunk_array *chunks);
t_chunk_array   *create_chunk(t_stack *a);
void    push_chunks_to_b(t_algo *algo);
bool    is_in_chunk(int idx, t_chunk *chunk);

// ***** compress *****
void    compress(t_stack *a);
void    merge_sort(int *arr, int *temp, int left, int right);
int     binary_search(int *sorted, int size, int target);

// ***** cost *****
t_cost  find_cheapest_move(t_algo *algo);
void    execute_move(t_algo *algo, t_cost *cost);

// ***** final_rotate *****
int     find_min_pos(t_stack *a);
void    final_rotate_to_min(t_algo *algo);

// ***** insertion *****
void    push_back_to_a(t_algo *algo);

// ***** lis *****
t_lis*  init_lis(int size);
void    free_lis(t_lis *lis);
int     lis_binary_search(int *tail, int len, int target);
void    compute_lis(t_lis *lis, int *indices, int size);
void    mark_lis_els(t_stack *a, t_lis *lis);
void    calculate_lis(t_stack *a);
void    count_non_lis(t_stack *a);
bool    is_in_lis(t_stack *a, int pos);

// ***** named operations *****
void    pa(t_algo *algo);
void    pb(t_algo *algo);
void    sa(t_algo *algo);
void    sb(t_algo *algo);
void    ss(t_algo *algo);
void    ra(t_algo *algo);
void    rb(t_algo *algo);
void    rr(t_algo *algo);
void    rra(t_algo *algo);
void    rrb(t_algo *algo);
void    rrr(t_algo *algo);

// ***** operations *****
void    push(t_stack *src, t_stack *dst);
void    swap(t_stack *stack);
void    rotate(t_stack *stack);
void    reverse_rotate(t_stack *stack);

// ***** t_stack utils *****
bool    parse(t_stack *a, t_stack *b, int argc, char **argv);
int     init_stack(t_stack *s, int capacity);
void    free_stack(t_stack *s);

// ***** position_bst *****
t_node_pos  *create_position_tree(t_stack *a);
int         find_target_pos(t_node_pos *root, int b_idx, t_stack *a);
void        free_pos_tree(t_node_pos *root);

// ***** small sort *****
bool    is_sorted(t_stack *s);
void    sort_three(t_algo *algo);
void    sort_five(t_algo *algo);

// ***** split *****
char	**ft_split(char const *s, char c);

// ***** t_stack utils *****
int init_stack(t_stack *s, int capacity);

// ***** utils *****
int     ft_atoi(const char *str);
size_t  ft_strlen(char *str);
void	output_message(char *str);
void	print_t_stack(t_stack *s);
void    copy_stack(int *cpy, t_stack *a);

