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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// ***** algo *****
int				init_algo(t_algo *algo, t_stack *a, t_stack *b);
void			rotate_to_top(t_stack *s, int pos, t_algo *algo, char c);
void			smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c);
void			sort(t_algo *algo);
void			sort_large_stack(t_algo *algo);

// ***** alone *****
t_cost			calculate_move_cost(t_algo *algo, int b_idx);
void			free_split(char **array);

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

// ***** cost utils *****
void			calculate_cost_a(t_cost *cost, t_stack *a, int target_pos);
void			calculate_cost_b(t_cost *cost, t_stack *b, int target_pos);
int				optimize_combined_cost(t_cost *cost);
int				find_target_pos(int b_idx, t_stack *a);

// ***** final_rotate *****
int				find_min_pos(t_stack *a);
void			final_rotate_to_min(t_algo *algo);

// ***** insertion *****
void			push_back_to_a(t_algo *algo);
void			push_back_simple(t_algo *algo);

// ***** lis *****
void			compute_lis(t_lis *lis, int *indices, int size);
void			mark_lis_els(t_stack *a, t_lis *lis);
void			calculate_lis(t_stack *a);
bool			is_in_lis(t_stack *a, int pos);

// ***** lis utils *****
t_lis			*init_lis(int size);
void			get_non_lis_range(t_stack *a, int *min_idx, int *max_idx);
void			free_lis(t_lis *lis);
void			count_non_lis(t_stack *a);
int				lis_binary_search(int *tail, int len, int target);

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

// ***** parsing utils *****
size_t			split_len(char **str);
bool			is_valid(char **str, t_stack *s, size_t len);

// ***** parsing *****
void			push_element(t_stack *s, int nbr);
bool			validate_all_strings(char **str, size_t len);
bool			parse(t_stack *a, t_stack *b, int argc, char **argv);

// ***** t_stack utils *****
int				init_stack(t_stack *s, int capacity);
void			free_both_stacks(t_stack *a, t_stack *b);

// ***** small sort *****
bool			is_sorted(t_stack *s);
void			sort_three(t_algo *algo);

// ***** sort medium stack *****
int				find_index_pos(t_stack *s, int target_idx);
void			push_to_b_optimized(t_algo *algo, int pos);
void			sort_medium_stack(t_algo *algo);

// ***** sort large stack *****
void			sort_large_stack(t_algo *algo);

// ***** sort large utils *****
void			init_chunk_ctx(t_chunk_ctx *ctx, int size);
void			init_push_ctx(t_push_ctx *ctx, int size);
int				get_chunks(int size);
void			sort_remaining_in_a(t_algo *algo);
void			rotate_b_if_needed(t_algo *algo, t_push_ctx *ctx);

// ***** sort large utils 2 *****
void			smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c);
int				calculate_cost(t_algo *algo, int i);
int				find_best_element(t_algo *algo, t_push_ctx *ctx);

// ***** split *****
char			**ft_split(char const *s, char c);

// ***** t_stack utils *****
int				init_stack(t_stack *s, int capacity);

// ***** utils *****
long long		ft_atoi(const char *str);
size_t			ft_strlen(char *str);
void			output_message(char *str);
void			copy_stack(int *cpy, t_stack *a);
int				int_sqrt(int n);
