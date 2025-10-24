/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:21 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/24 14:24:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// fist el of the string --> top of the stack so add from the end 

int main(int argc, char **argv)
{
    Stack   a;
    Stack   b;
    size_t  capacity;

    if (argc < 2)
        return (1);
    if (argc == 2)
        capacity = ft_strlen(argv[1]);
    else 
        capacity = argc - 1; 
    if (!init_stack(&a, capacity) || !init_stack(&b, capacity))
    {
        DEBUG_LOG("%sError: %sMalloc failure in init_stacks", RED, RESET);
        return (1);
    }
    if (!parse(&a, argc, argv))
    {
        DEBUG_LOG("%sError: %sParsing", RED, RESET);
        return (1);
    }
    sort(&a, &b);
    return (0);
}