/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_bst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:46:36 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/17 15:09:31 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node_pos  *insert_pos_node(t_node_pos *root, int index, int pos)
{
    if (!root)
    {
        root = malloc(sizeof(t_node_pos));
        if (!root)
            return (NULL);
        root->idx = index;
        root->stack_pos = pos;
        root->left = NULL;
        root->right = NULL;
        return (root);
    }
    if (index < root->idx)
        root->left = insert_pos_node(root->left, index, pos);
    else
        root->right = insert_pos_node(root->right, index, pos);
    return (root);
}

t_node_pos  *create_position_tree(t_stack *a)
{
    t_node_pos  *root;
    int         i;

    root = NULL;
    i = 0;
    while (i <= a->top)
    {
        root = insert_pos_node(root, a->indices[i], i);
        i++;
    }
    return (root);
}

void    wrap_around(t_stack *a, int *best_pos)
{
    int min_val;
    int i;
    
    min_val = INT_MAX;
    i = 0;
    while (i <= a->top)
    {
        if (a->indices[i] < min_val)
        {
            min_val = a->indices[i];
            *best_pos = i;
        }
        i++;
    }
}

int find_target_pos(t_node_pos *root, int b_idx, t_stack *a)
{
    int best_pos;
    int i;
    int closest_bigger;
    (void)root; // WHY NOT USED ?? 
    
    i = 0;
    while (i <= a->top)
    {
        if (a->indices[i] > b_idx && a->indices[i] < closest_bigger)
        {
            closest_bigger = a->indices[i];
            best_pos = i;
        }
        i++;
    }
    if (closest_bigger == INT_MAX)
        wrap_around(a, &best_pos);
    return (best_pos);
}

void    free_pos_tree(t_node_pos *root)
{
    if (!root)
        return;
    free_pos_tree(root->left);
    free_pos_tree(root->right);
    free(root);
}
