/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:28 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/28 11:57:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

#ifdef DEBUG_MODE
    #define DEBUG_LOG(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#else 
    #define DEBUG_LOG(fmt, ...) ((void)0)
#endif

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	char	**str;
}	t_split;

typedef struct {
    int     *values;
    int     top;
    size_t  capacity;
}   Stack;

// ***** stack utils *****
bool    parse(Stack *a, Stack *b, int argc, char **argv);

// ***** stack utils *****
char	**ft_split(char const *s, char c);

// ***** stack operations *****
void    push(Stack *s, int value);

// ***** stack utils *****
int init_stack(Stack *s, int capacity);

// ***** stack utils *****
int     ft_atoi(const char *str);
size_t  ft_strlen(char *str);
void	output_message(char *str);
