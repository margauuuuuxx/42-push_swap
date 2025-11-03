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

int init_t_stack(t_stack *s, int capacity) {
    s->values = malloc(sizeof(int) * capacity);
    if (!s->values)
        return (0);
    s->top = -1;
    s->capacity = capacity;
    return (1);
}