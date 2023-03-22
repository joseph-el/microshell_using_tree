/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:20:36 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/03/22 11:41:30 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "microshell.h"

static void    run_cmdlist(t_tree *root, char **envp)
{
    pid_t   pid;
    
    if (!root)
        return ;
    if (IS_CD(*root->cmdexc))
        return (ft_cd(root->cmdexc));
    pid = fork();
    if (pid == 0)
    {
        if (!*root->cmdexc)
            exit(0);
        execve(*root->cmdexc, root->cmdexc, envp);
        EXEC_ERR(*root->cmdexc);
        exit(EXIT_FAILURE);
    }
    waitpid(pid, NULL, 0);
    return ;
}

static void    run_fg(t_tree *left, t_tree *right, char **envp)
{
    tree_executor(left, envp);
    tree_executor(right, envp);
}

static void    run_pipeline(t_tree *left, t_tree *right, char **envp)
{
    int     fds[2];

    pipe(fds);
    if (fork() == 0)
    {
        close(STDOUT_FILENO);
        dup2(fds[WRITE_END], 1);
        FT_CLOSE(fds[READ_END], fds[WRITE_END]);
        tree_executor(left, envp);
        exit(EXIT_SUCCESS);
    }
    if (fork() == 0)
    {
        close(STDIN_FILENO);
        dup2(fds[READ_END], 0);
        FT_CLOSE(fds[READ_END], fds[WRITE_END]);
        tree_executor(right, envp);
        exit(EXIT_SUCCESS);
    }
    FT_CLOSE(fds[READ_END], fds[WRITE_END]);
    while (waitpid(-1, NULL, 0) != -1);
    return ;
}

void    tree_executor(t_tree *root, char **envp)
{
    if (!root)
        return ;
    if (root->type == CMDEXC)
        return (run_cmdlist(root, envp));
    else if (root->type == FG)
        return (run_fg(root->left, root->right, envp));
    else if (root->type == PIPE)
        return (run_pipeline(root->left, root->right, envp));
    return ;
}