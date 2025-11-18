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
