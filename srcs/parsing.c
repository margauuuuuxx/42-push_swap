/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:21:52 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 14:09:48 by marlonco         ###   ########.fr       */
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

void    push_element(t_stack *s, int nbr)
{
    if (s->top + 1 < s->capacity)
    {
        s->values[++s->top] = nbr;
        s->indices[s->top] = -1;
        s->in_LIS[s->top] = false;
    }
}

static bool no_duplicates(t_stack *s)
{
    int i;
    int j;

    i = 0;
    while (i < s->top)
    {
        j = i + 1;
        while (j <= s->top)
        {
            if (s->values[i] == s->values[j])
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}

static bool is_valid(char **str, t_stack *s, size_t len) 
{
    int i;
    int j;
    int count;
    
    if (len == 0)
        return (false);
    i = 0;
    while (i < (int)len) {
        if (!str[i] || str[i][0] == '\0')
            return (false);
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
        i++;
    }
    i = (int)len - 1;
    while (i >= 0) {
        push_element(s, ft_atoi(str[i]));
        i--;
    }
    return (no_duplicates(s));
}

bool    parse(t_stack *a, t_stack *b, int argc, char **argv)
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
        DEBUG_LOG("%sError: %sMalloc failure in init_t_stacks", RED, RESET);
        return (false);
    }
    return (is_valid(split_str, a, capacity));
}
