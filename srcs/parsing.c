/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:21:52 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/31 09:28:03 by marlonco         ###   ########.fr       */
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

static bool is_valid(char **str, Stack *s, size_t len) 
{
    int i;
    int j;
    int count;
    
    i = len - 1;
    while (i >= 0) {
        j = ft_strlen(str[i]) - 1;
        count = 0;
        while (j >= 0) {
            if (((str[i][j] < '0' || str[i][j] > '9') 
                && (str[i][j] != '+' && str[i][j] != '-'))
                || count > 1)
                return (false);
            if (str[i][j] == '+' || str[i][j] == '-') {
                if (j != 0)
                    return (false);
                count++;
            }
            j--;
        }
        push(s, ft_atoi(str[i]));
        i--;
    }
    return (true);
}

bool    parse(Stack *a, Stack *b, int argc, char **argv)
{
    char    **split_str;
    size_t  capacity;

    if (argc == 2) {
        split_str = ft_split(argv[1], ' ');
        capacity = split_len(split_str);
    }
    else {
        split_str = &argv[1];
        capacity = argc - 1;
    }
    if (!init_stack(a, capacity) || !init_stack(b, capacity))
    {
        DEBUG_LOG("%sError: %sMalloc failure in init_stacks", RED, RESET);
        return (1);
    }
    return (is_valid(split_str, a, capacity));
}