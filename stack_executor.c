/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:11:28 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/03/27 23:59:56 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "microshell.h"

void    ft_cd(char **args)
{
    int index;
    int change;
    
    index = 0;
    while (args[index])
        index ++;
    if (index != 2)
    {
        CD_ERR(1, NULL);
        return ;
    }
    change = chdir(args[1]);
    if (change < 0)
    {
        CD_ERR(0, args[1]);
        return ;
    }
    return ;
}

static void    run_cmd(t_stack *root, char **envp, int fds[2], int fd_tmp, int flag)
{
    pid_t   pid;

    if (*root->cmdexc && IS_CD(*root->cmdexc) && flag & ~(INPUT | PROCESS | OUTPUT))
        return (ft_cd(root->cmdexc));
    pid = fork();
    if (pid == 0)
    {
        if (flag & (INPUT | PROCESS | OUTPUT))
            close(*fds);
        if (flag & INPUT)
            dup2(fds[1], 1);
        if (flag & PROCESS)
        {
            dup2(fd_tmp, 0);
            dup2(fds[1], 1);
        }
        if (flag & OUTPUT)
            dup2(fd_tmp, 0);
        execve(*root->cmdexc, root->cmdexc, envp);
        EXEC_ERR(*root->cmdexc);
        exit(1);
    }
    waitpid(pid, NULL, 0);
}

static void    pipe_line(t_stack **root, char **envp)
{
    int fds[2];
    int fd_tmp;

    fd_tmp = 0;
    while ((*root) && (*root)->type != FG)
    {
        pipe(fds);
        if ((*root)->type == PIPE)
        {
            (*root) = (*root)->next;
            continue;
        }
        if (!(*root)->prev)
            run_cmd((*root), envp, fds, fd_tmp, INPUT);
        else if (!(*root)->next || ((*root)->next && (*root)->next->type == FG))
            run_cmd((*root), envp, fds, fd_tmp, OUTPUT);
        else
            run_cmd((*root), envp, fds, fd_tmp, PROCESS);
        close(fd_tmp);
        fd_tmp = dup(fds[0]);
        close(fds[0]);
        close(fds[1]);
        (*root) = (*root)->next;
    }
        close(fd_tmp);
        close(fds[0]);
        close(fds[1]);
}

static int  is_pipe_fg(t_stack *root, int size, int flag)
{
    while (root)
    {
        if (flag == F_PIPE && root->type == PIPE)
            return (1);
        else if (flag == F_PIPE_FG && root->type == PIPE && root->size < size)
            return (1);
        else if (flag == F_FG && root->type == FG)
            return (root->size);
        root = root->next;
    }
    return (-1);
}

void    stack_executor(t_stack *root, char **envp)
{
    int fg;
    
    if (!root)
        return ;
    while (root)
    {
        fg = is_pipe_fg(root, 0, F_FG);
        if (fg != -1)
        {
            if (is_pipe_fg(root, fg, F_PIPE_FG) != -1)
                pipe_line(&root, envp);
            else
            {
                run_cmd(root, envp, NULL, 0, 0);
                root = root->next;
            }
            root = root->next;
            // fprintf(stderr, "check type |%d|\n", root->type);
        }
        else if (is_pipe_fg(root, 0, F_PIPE) != -1)
            pipe_line(&root, envp);
        else if (!root->next)
        {
            run_cmd(root, envp, NULL, 0, 0);
            root = root->next;
        }
    }
}







