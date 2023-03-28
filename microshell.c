/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:08:03 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/03/27 23:59:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "microshell.h"

int main(int argc, char **argv, char **envp)
{
    t_stack  *exec = NULL;
    t_tree   *root = NULL;

    (void)argc;
    (void)exec;
    argv++;
    root = parcer(&argv);
    if (!root)
        return (exit(EXIT_FAILURE), 1);

    /** 1
     * @brief stack executor
     * @param t_stack *root
     * @param char **envp |
     */

    // set_executor(&exec, root, 0);
    // stack_executor(exec, envp);

    /** 2
     * @brief traversal executor
     * @param t_tree *root
     * @param char **envp
     */
    
    tree_executor(root, envp);
    exit(EXIT_SUCCESS);
}