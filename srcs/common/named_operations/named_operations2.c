/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   named_operations2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:09:32 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:09:35 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/push_swap.h"

void	ra(t_algo *algo)
{
	rotate(algo->a);
	if (write(1, "ra\n", 3) < 0)
		return ;
}

void	rb(t_algo *algo)
{
	rotate(algo->b);
	if (write(1, "rb\n", 3) < 0)
		return ;
}

void	rr(t_algo *algo)
{
	rotate(algo->a);
	rotate(algo->b);
	if (write(1, "rr\n", 3) < 0)
		return ;
}

void	rra(t_algo *algo)
{
	reverse_rotate(algo->a);
	if (write(1, "rra\n", 4) < 0)
		return ;
}

void	rrb(t_algo *algo)
{
	reverse_rotate(algo->b);
	if (write(1, "rrb\n", 4) < 0)
		return ;
}
