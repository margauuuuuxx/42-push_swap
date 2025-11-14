/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_bst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:46:36 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/14 12:51:06 by marlonco         ###   ########.fr       */
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