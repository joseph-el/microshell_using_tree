/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:03:45 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/03/22 11:07:42 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "microshell.h"

t_tree  *new_node(t_tree *left, t_tree *right, char **cmdexc, t_type type)
{
    t_tree  *s_node;

    s_node = malloc(sizeof(t_tree));
    if (!s_node)
        {FATAL_ERR};
    s_node->cmdexc = cmdexc;
    s_node->right = right;
    s_node->left = left;
    s_node->type = type;
    return (s_node);
}

t_tree  *parce_cmdlist(char ***argv)
{
    t_tree  *root;

    if (!**argv)
        return (NULL);
    root = new_node(NULL, NULL, *argv, CMDEXC);
    while (**argv && !IS_PIPE(**argv) && !IS_FG(**argv))
        (*argv) ++;
    return (root);
}

t_tree  *parce_pipeline(char ***argv)
{
    t_tree  *root;

    if (!**argv)
        return (NULL);
    root = parce_cmdlist(argv);
    if (!root)
        return (NULL);
    while (**argv && IS_PIPE(**argv))
    {
        (**argv = NULL, (*argv)++);
        root = new_node(root, NULL, NULL, PIPE);
        root->right = parce_cmdlist(argv);
        if (!root->right)
            return (NULL);
    }
    return (root);
}

t_tree  *parcer(char ***argv)
{
    t_tree  *root;

    if (!**argv)
        return (NULL);
    root = parce_pipeline(argv);
    if (!root)
        return (NULL);
    if (**argv && IS_FG(**argv))
    {
        (**argv = NULL, (*argv)++);
        root = new_node(root, parcer(argv), NULL, FG);
    }
    return (root);
}