/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:31:35 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/03 14:21:34 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
    The goal is to find elements already in correct relative order
        --> referring to *indices NOT *values of stack
*/

int lis_binary_search(int *tail, int len, int target)
{
    int left; 
    int right;
    int mid;

    left = 0;
    right = len;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (tail[mid] < target)
            left = mid + 1;
        else 
            right = mid;
    }
    return (left);
}

void    free_lis(t_lis *lis)
{
    free(lis->lens);
    free(lis->prev);
    free(lis->tail);
    free(lis);
}

t_lis   *init_lis(int size)
{
    int     i;
    t_lis   *lis;

    i = 0;
    lis = malloc(sizeof(t_lis));
    lis->lens = malloc(size * sizeof(int));
    lis->prev = malloc(size * sizeof(int));
    lis->tail = malloc(size * sizeof(int));
    if (!lis || !lis->lens || !lis->prev || !lis->tail)
    {
        DEBUG_LOG("%sError: %sMalloc failure in init_lis", RED, RESET);
        return (NULL);
    }
    while (i < size)
    {
        lis->lens[i] = 0;
        i++;
    }
    lis->max_len = 0;
    return (lis);
}

void    compute_lis(t_lis *lis, int *indices, int size)
{
    int len;
    int pos;
    int i;

    len = 0;
    i = 0;
    while (i < size)
    {   
        pos = lis_binary_search(lis->tail, len, indices[i]);
        lis->tail[pos] = indices[i];
        lis->lens[i] = pos + 1;
        if (pos > 0)
            lis->prev[i] = lis->tail[pos - 1];
        else
            lis->prev[i] = -1;
        if (pos == len)
            len++;
        i++;
    }
    lis->max_len = len;
}

// set a->in_LIS[i]
void    mark_lis_els(t_stack *a, t_lis *lis)
{
    int max_idx; // ending position of LIS
    int i;
    int current_val;

    max_idx = -1;
    i = 0;
    while (i <= a->top)
    {
        if (lis->lens[i] == lis->max_len)
        {
            max_idx = i;
            break;
        }
        i++;
    }
    if (max_idx == -1)
        return;
    a->in_LIS[max_idx] = true;
    current_val = lis->prev[max_idx];
    if (current_val == -1)
        return;
    i = max_idx - 1;
    while (i >= 0)
    {
        if (a->indices[i] == current_val)
        {
            a->in_LIS[i] = true;
            if (lis->prev[i] != -1)
                current_val = lis->prev[i];
            else 
                break;
        }
        i--;
    }
}

void count_non_lis(t_stack *a)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while (i <= a->top)
    {
        if (!a->in_LIS[i])
            count++;
        i++;
    }
    a->not_in_lis = count;
}

bool    is_in_lis(t_stack *a, int pos)
{
    if (a->in_LIS[pos])
        return (true);
    return (false);
}

void    calculate_lis(t_stack *a)
{
    t_lis *lis;

    lis = init_lis(a->top + 1);
    compute_lis(lis, a->indices, a->top + 1);
    mark_lis_els(a, lis);
    count_non_lis(a);
    free_lis(lis);    
}
