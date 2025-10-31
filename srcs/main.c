/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:21 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/31 09:33:32 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// fist el of the string --> top of the stack so add from the end 

int main(int argc, char **argv)
{
    Stack   a;
    Stack   b;

    if (argc < 2) {
        output_message("Error: Please submit at least one argument ...\n");
        return (1);
    }
    if (!parse(&a, &b, argc, argv))
    {
        output_message("Error: Invalid character in argument ...\n");
        return (1);
    }
    print_stack(&a);
    //sort(&a, &b);
    return (0);
}