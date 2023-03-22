/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/03/22 11:43:35 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MICROSHELL_H
# define MICROSHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define INPUT (1 << 1)
# define OUTPUT (1 << 2)
# define PROCESS (1 << 3)
# define F_PIPE_FG (1 << 4)
# define F_FG (1 << 5)
# define F_PIPE (1 << 6)
# define WRITE_END 1
# define READ_END 0

# define FATAL_ERR  ft_putstr(2, "error: fatal\n"); exit(1);

# define EXEC_ERR(target) ft_putstr(2, "error: cannot execute "); ft_putstr(2, target); ft_putstr(2, "\n");

# define IS_PIPE(target) (strncmp(target, "|", sizeof("|") + 1) == 0)

# define IS_FG(target) (strncmp(target, ";", sizeof(";") + 1) == 0)

# define FT_CLOSE(fd1, fd2) close(fd1); close(fd2);

# define IS_CD(target) (strncmp(target, "cd", sizeof("cd") + 1) == 0)

# define CD_ERR(ERR, TARGET) if (ERR == 1) {ft_putstr(2, "error: cd: bad arguments\n");} \
    else {ft_putstr(2, "error: cd: cannot change directory to "); ft_putstr(2, TARGET); ft_putstr(2, "\n");}

typedef enum s_type
{
    CMDEXC,
    PIPE,
    FG
}           t_type;

typedef struct s_tree
{
    t_type          type;
    char            **cmdexc;
    struct s_tree   *left;
    struct s_tree   *right;
}               t_tree;

typedef struct s_stack
{
    t_type          type;
    int              size;
    char          **cmdexc;
    struct s_stack  *next;
    struct s_stack  *prev;
}               t_stack;

/**
 * @brief parser utils
 * @param  ***argv
 * @return t_tree* 
 */

t_tree  *new_node(t_tree *left, t_tree *right, char **cmdexc, t_type type);
t_tree  *parce_pipeline(char ***argv);
t_tree  *parce_cmdlist(char ***argv);
t_tree  *parcer(char ***argv);

/**
 * @brief Set the stack object
 * 
 * @param list 
 * @param root 
 * @param level 
 */

void    set_stack(t_stack **list, t_tree *root, int level);
void    add_back(t_stack **list, t_stack *new);
t_stack *new_node_exc(t_type type, char **cmdexc);

/**
 * @brief executor exect by (stack | tree traversal)
 * 
 * @param root 
 * @param envp 
 */

void    stack_executor(t_stack *root, char **envp);
void    tree_executor(t_tree *root, char **envp);


void    ft_putstr(int fd, char *error);
void    ft_cd(char **args);

# endif