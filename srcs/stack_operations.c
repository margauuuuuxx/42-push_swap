/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:25 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/24 14:13:39 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    push(Stack *s, int value) {
    if (s->top + 1 > s->capacity)
    {
        DEBUG_LOG("%SError: %sPush: stack is full", RED, RESET);
        return;
    }
    s->values[s->top++] = value;
}