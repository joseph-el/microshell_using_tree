/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:08:42 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/03/22 11:54:57 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "microshell.h"

t_stack  *new_node_exc(t_type type, char **cmdexc)
{
    t_stack *new;

    new = malloc(sizeof(t_stack));
    if (!new)
        {FATAL_ERR};
    new->next = new->prev = NULL;
    new->cmdexc = cmdexc;
    new->type = type;
    return (new);
}

void    add_back(t_stack **list, t_stack *new)
{
    t_stack *tmp;
    
    
    if (!(*list))
        ((*list) = new, new->size = 1);
    else
    {
        tmp = (*list);
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
        new->size = tmp->size + 1;
    }
}

void    set_stack(t_stack **list, t_tree *root, int level)
{
    if (!root)
        return ;
    if (root->type == CMDEXC)
    {
        add_back(list, new_node_exc(CMDEXC, root->cmdexc));
    }
    if (root->type == PIPE)
    {
        set_stack(list, root->left, level + 1);
        add_back(list, new_node_exc(PIPE, NULL));
        set_stack(list, root->right, level + 1);
    }
    if (root->type == FG)
    {
        set_stack(list, root->left, level + 1);
        add_back(list, new_node_exc(FG, NULL));
        set_stack(list, root->right, level + 1);
    }
    return ;
}

void    ft_putstr(int fd, char *str)
{
    if (str)
    {
        while (*str)
            write(fd, str++, 1);
    }
}
