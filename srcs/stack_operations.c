/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:25 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/31 09:36:31 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    push(t_stack *s, int value) {
    if (s->top + 1 > (int)s->capacity)
    {
        DEBUG_LOG("%sError: %sPush: t_stack is full", RED, RESET);
        return;
    }
    s->values[++s->top] = value;
}

void    pop(t_stack *s) {
    if (s->top > -1)
        s->top--;
}

int top(t_stack *s) {
    if (s->top > -1)
        return (s->values[s->top]);
    return (-1);
}