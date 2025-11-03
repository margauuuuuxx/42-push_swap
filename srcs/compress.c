/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:39:23 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/03 11:58:05 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void    merge(int *arr, int *temp, t_merge *m)
{
    int i;
    int j;
    int k;

    i = m->left;
    while (i <= m->right)
    {
        temp[i] = arr[i];
        i++;
    }
    i = m->left;
    j = m->mid + 1;
    k = m->left;
    while (i <= m->mid && j <= m->right)
    {
        if (temp[i] <= temp[j])
            arr[k++] = temp[i++];
        else 
            arr[k++] = temp[j++];
    }
    while (i <= m->mid)
        arr[k++] = temp[i++];
    while (j <= m->right)
        arr[k++] = temp[j++];
}

void    merge_sort(int *arr, int *temp, int left, int right) 
{
    t_merge m;
    int     mid;

    m.left = left;
    m.right = right;
    if (left < right)
    {
        mid = left + (right - left) / 2;
        m.mid = mid;
        merge_sort(arr, temp, left, mid);
        merge_sort(arr, temp, mid + 1, right);
        merge(arr, temp, &m);
    }
}

int binary_search(int *sorted, int size, int target)
{
    t_merge m;

    m.left = 0;
    m.right = size - 1;
    while (m.left <= m.right)
    {
        m.mid = m.left + (m.right - m.left) / 2;
        if (sorted[m.mid] == target)
            return (m.mid);
        else if (sorted[m.mid] < target)
            m.left = m.mid + 1;
        else 
            m.right = m.mid - 1;
    }
    return (-1);
}

static void map(int *cpy, int *temp, t_stack *a) {
    int i;

    i = 0;
    while (i <= a->top)
    {
        a->indices[i] = binary_search(cpy, a->top + 1, a->values[i]);
        i++;
    }
    free(cpy);
    free(temp);
}

void    compress(t_stack *a)
{
    int *cpy;
    int *sorted;

    cpy = malloc(a->capacity * sizeof(int));
    sorted = malloc(a->capacity * sizeof(int));
    if (!cpy || !sorted)
        return;
    copy_stack(cpy, a);
    merge_sort(cpy, sorted, 0, a->top);
    map(cpy, sorted, a);
}
