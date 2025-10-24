/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:42:28 by marlonco          #+#    #+#             */
/*   Updated: 2025/10/24 14:22:38 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

typedef struct {
    int     *values;
    int     top;
    size_t  capacity;
}   Stack;

// ***** stack utils *****
int init_stack(Stack *s, int capacity);