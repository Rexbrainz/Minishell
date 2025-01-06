#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_file_node
{
    char *filename;
    int type;
    struct s_file_node *next;
}   t_file_node;

typedef struct s_file_list
{
    t_file_node *head;
    t_file_node *tail;
    int         size;
} t_file_list;

typedef struct s_node
{
    char **cmd;
    int type;
    t_file_list *file_list;
    struct s_node *next;
} t_node;

typedef struct s_command_list
{
    t_file_node *head;
    t_file_node *tail;
    int         size;
} t_command_list;

#endif