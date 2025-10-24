/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:21:52 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/24 14:29:49 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int is_valid(char *str) 
{
    int i;
    int sign;
    
    i = 0;
}

static bool parse_single(Stack *s, char *str) 
{

}

static bool parse_multi(Stack *s, int argc, char **argv)
{
    int i;

    i = argc - 1;
    while (i >= 1)
    {
        if (!is_valid(argv[i]))
            return (false);
    }
    return (true);
}

bool    parse(Stack *s, int argc, char **argv)
{
    if (argc == 2)
        return (parse_single(s, argv[1]));
    else
        return (parse_multi(s, argc, argv));
}