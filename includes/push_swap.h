/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:28 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:38:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// #ifdef DEBUG_MODE
// # define DEBUG_LOG(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)
// #else
// # define DEBUG_LOG(fmt, ...) ((void)0)
// #endif

// ***** algo *****
int				init_algo(t_algo *algo, t_stack *a, t_stack *b);
void			rotate_to_top(t_stack *s, int pos, t_algo *algo, char c);
void			smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c);
void			sort(t_algo *algo);
void			sort_large_stack(t_algo *algo);

// ***** chunk *****
void			free_chunk_array(t_chunk_array *chunks);
t_chunk_array	*create_chunk(t_stack *a);
void			push_chunks_to_b(t_algo *algo);
bool			is_in_chunk(int idx, t_chunk *chunk);

// ***** compress *****
void			compress(t_stack *a);
void			merge_sort(int *arr, int *temp, int left, int right);
int				binary_search(int *sorted, int size, int target);

// ***** cost *****
t_cost			find_cheapest_move(t_algo *algo);
void			execute_move(t_algo *algo, t_cost *cost);

// ***** final_rotate *****
int				find_min_pos(t_stack *a);
void			final_rotate_to_min(t_algo *algo);

// ***** insertion *****
void			push_back_to_a(t_algo *algo);

// ***** lis *****
t_lis			*init_lis(int size);
void			free_lis(t_lis *lis);
int				lis_binary_search(int *tail, int len, int target);
void			compute_lis(t_lis *lis, int *indices, int size);
void			mark_lis_els(t_stack *a, t_lis *lis);
void			calculate_lis(t_stack *a);
void			count_non_lis(t_stack *a);
bool			is_in_lis(t_stack *a, int pos);

// ***** named operations *****
void			pa(t_algo *algo);
void			pb(t_algo *algo);
void			sa(t_algo *algo);
void			sb(t_algo *algo);
void			ss(t_algo *algo);

// ***** named operations 2 *****
void			ra(t_algo *algo);
void			rb(t_algo *algo);
void			rr(t_algo *algo);
void			rra(t_algo *algo);
void			rrb(t_algo *algo);

// ***** operations *****
void			push(t_stack *src, t_stack *dst);
void			swap(t_stack *stack);
void			rotate(t_stack *stack);
void			reverse_rotate(t_stack *stack);
void			rrr(t_algo *algo);

// ***** t_stack utils *****
bool			parse(t_stack *a, t_stack *b, int argc, char **argv);
int				init_stack(t_stack *s, int capacity);
void			free_stack(t_stack *s);

// ***** small sort *****
bool			is_sorted(t_stack *s);
void			sort_three(t_algo *algo);
void			sort_five(t_algo *algo);

// ***** sort small stack *****
int				find_index_pos(t_stack *s, int target_idx);
void			push_to_b_optimized(t_algo *algo, int pos);
void			sort_small_stack(t_algo *algo);

// ***** sort medium stack *****
void			sort_medium_stack(t_algo *algo);

// ***** split *****
char			**ft_split(char const *s, char c);

// ***** t_stack utils *****
int				init_stack(t_stack *s, int capacity);

// ***** utils *****
int				ft_atoi(const char *str);
size_t			ft_strlen(char *str);
void			output_message(char *str);
void			print_t_stack(t_stack *s);
void			copy_stack(int *cpy, t_stack *a);

void			turk_sort(t_algo *algo);
