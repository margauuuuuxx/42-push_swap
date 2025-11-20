/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   named_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:14:59 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 13:38:28 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	pa(t_algo *algo)
{
	if (algo->b->top < 0)
		return ;
	push(algo->b, algo->a);
	if (write(1, "pa\n", 3) < 0)
		return ;
}

void	pb(t_algo *algo)
{
	if (algo->a->top < 0)
		return ;
	push(algo->a, algo->b);
	if (write(1, "pb\n", 3) < 0)
		return ;
}

void	sa(t_algo *algo)
{
	swap(algo->a);
	if (write(1, "sa\n", 3) < 0)
		return ;
}

void	sb(t_algo *algo)
{
	swap(algo->b);
	if (write(1, "sb\n", 3) < 0)
		return ;
}

void	ss(t_algo *algo)
{
	swap(algo->a);
	swap(algo->b);
	if (write(1, "ss\n", 3) < 0)
		return ;
}
