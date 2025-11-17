/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:21 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 14:35:35 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// fist el of the string --> top of the t_stack so add from the end 
// GOAL: smallest nbr at the topok

int main(int argc, char **argv)
{
    t_stack         a;
    t_stack         b;
    t_algo          algo;

    if (argc < 2)
        return (output_message("Error: Please submit at least one argument ...\n"), 1);
    if (!parse(&a, &b, argc, argv))
        return (output_message("Error: Invalid character in argument ...\n"), 1);
    compress(&a);
    if (is_sorted(&a))
    {
        free_stack(&a);
        free_stack(&b);
        return (0);
    }
    calculate_lis(&a);
    if (init_algo(&algo, &a, &b))
        return (output_message("Error: Init algo\n"), 1);
    sort(&algo);
    free_chunk_array(algo.chunks);
    free_stack(&a);
    free_stack(&b);
    return (0);
}
