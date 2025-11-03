/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:28 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/31 10:35:29 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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
    struct s_node_pos   left;
    struct s_node_pos   right;
}   t_node_pos;

typedef struct s_chunk {
    int min_idx; // min idx in chunk
    int max_idx; // max idx in chunk
    int size;
}   t_chunk;

typedef struct s_lis {
    int *lens; // lens of LIS ending at i
    int *prev; // previous els in LIS
    int *tail; // smallest tail for each len
    int max_len; // max LIS len 
}   t_lis;

typedef struct s_algo {
    t_stack     *a;
    t_stack     *b;
    t_node_pos  *pos_tree;
    t_chunk     *chunks;
    int         chunk_count;
}   t_algo;

// ***** t_stack utils *****
bool    parse(t_stack *a, t_stack *b, int argc, char **argv);

// ***** t_stack utils *****
char	**ft_split(char const *s, char c);

// ***** t_stack operations *****
void    push(t_stack *s, int value);
void    pop(t_stack *s);
int top(t_stack *s);

// ***** t_stack utils *****
int init_t_stack(t_stack *s, int capacity);

// ***** utils *****
int     ft_atoi(const char *str);
size_t  ft_strlen(char *str);
void	output_message(char *str);
void	print_t_stack(t_stack *s);

