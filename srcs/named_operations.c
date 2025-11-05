/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   named_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:14:59 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/05 16:17:33 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    pa(t_algo *algo)
{
    if (b->top < 0)
        return;
    push(b, a);
    write(1, "pa\n", 3);
}

void    pb(t_algo *algo)
{
    if (a->top < 0)
        return;
    push(a, b);
    write(1, "pb\n", 3);
}

void    sa(t_algo *algo)
{
    swap(a);
    write(1, "sa\n", 3);
}

void    sb(t_algo *algo)
{
    swap(b);
    write(1, "sb\n", 3);
}

void    ss(t_algo *algo)
{
    swap(a);
    swap(b);
    write(1, "ss\n", 3);
}

void    ra(t_algo *algo)
{
    rotate(a);
    write(1, "ra\n", 3);
}

void    rb(t_algo *algo)
{
    rotate(b);
    write(1, "rb\n", 3);
}

void    rr(t_algo *algo)
{
    rotate(a);
    rotate(b);
    write(1, "rr\n", 3);
}

void    rra(t_algo *algo)
{
    reverse_rotate(a);
    write(1, "rra\n", 4);
}

void    rrb(t_algo *algo)
{
    reverse_rotate(b);
    write(1, "rrb\n", 4);
}

void    rrr(t_algo *algo)
{
    reverse_rotate(a);
    reverse_rotate(b);
    write(1, "rrr\n", 4);
} 