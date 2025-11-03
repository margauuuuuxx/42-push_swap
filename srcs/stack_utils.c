/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:57:48 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/24 14:18:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    free_stack(t_stack *s)
{
    free(s->values);
    free(s->indices);
    free(s->in_LIS);
    free(s);
}

int init_stack(t_stack *s, int capacity) {
    int i;

    i = 0;
    s->values = malloc(sizeof(int) * capacity);
    s->indices = malloc(sizeof(int) * capacity);
    s->in_LIS = malloc(sizeof(int) * capacity);
    if (!s->values || !s->indices || !s->in_LIS)
        return (0);
    while (i < capacity)
    {
        s->in_LIS[i] = false;
        i++;
    }
    s->top = -1;
    s->capacity = capacity;
    return (1);
}
