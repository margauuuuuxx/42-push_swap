/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:56:47 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:37:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	insert_all_from_b(t_algo *algo)
{
	t_cost	cheapest;

	while (algo->b->top >= 0)
	{
		cheapest = find_cheapest_move(algo);
		execute_move(algo, &cheapest);
	}
}

void	push_back_to_a(t_algo *algo)
{
	insert_all_from_b(algo);
	final_rotate_to_min(algo);
}

void	push_back_simple(t_algo *algo)
{
	int	mx_p;
	int	mx_v;
	int	i;

	while (algo->b->top >= 0)
	{
		mx_p = 0;
		mx_v = algo->b->indices[0];
		i = 1;
		while (i <= algo->b->top)
		{
			if (algo->b->indices[i] > mx_v)
			{
				mx_v = algo->b->indices[i];
				mx_p = i;
			}
			i++;
		}
		smart_rotate_to_top(algo->b, mx_p, algo, 'b');
		pa(algo);
	}
	final_rotate_to_min(algo);
}
