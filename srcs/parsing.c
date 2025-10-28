/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:21:52 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/28 11:59:48 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static size_t   split_len(char **str) {
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

static bool is_valid(char **str, Stack *s) 
{
    int i;
    int j;
    int count;
    
    i = 0;
    while (str[i]) {
        j = 0;
        count = 0;
        while (str[i][j]) {
            if (((str[i][j] < '0' || str[i][j] > '9') 
                && (str[i][j] != '+' && str[i][j] != '-'))
                || count > 1)
                return (false);
            if (str[i][j] == '+' || str[i][j] == '-') {
                if (j != 0 || !str[i][j + 1])
                    return (false);
                count++;
            }
            j++;
        }
        push(s, ft_atoi(str[i]));
        i++;
    }
    return (true);
}

bool    parse(Stack *a, Stack *b, int argc, char **argv)
{
    char    **split_str;
    int     capacity;

    if (argc == 2) {
        split_str = ft_split(argv[1], ' ');
        capacity = argc - 1;
    }
    else {
        split_str = argv;
        capacity = split_len(split_str);
    }
    if (!init_stack(a, capacity) || !init_stack(b, capacity))
    {
        DEBUG_LOG("%sError: %sMalloc failure in init_stacks", RED, RESET);
        return (1);
    }
    return (is_valid(split_str, a));
}