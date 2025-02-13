#include "../../Includes/minishell.h"

/*
	get current directory
	we are abusing getcwd
*/
void	ft_pwd(int update, t_commandlist *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(pwd);
	}
	clean_exit(update, cmd);
}

/*
	check if the variable exists
	go through the list and compare
*/
static int	compare_to_list(t_commandlist *cmd, char *str)
{
	int			place_in_list;
	t_envlist	*current;

	current = cmd->env->head;
	place_in_list = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, str) == 0)
			return (place_in_list);
		place_in_list++;
		current = current->next;
	}
	return (-1);
}

/*
	Case when the node to be removed is head
	extra if statement for same case as below
*/
static void	replace_head(t_commandlist *cmd)
{
	t_envlist	*current;
	t_envlist	*to_remove;

	to_remove = cmd->env->head;
	current = to_remove->next;
	free(to_remove->key);
	if (to_remove->value != NULL)
		free(to_remove->value);
	free(to_remove);
	cmd->env->head = current;
	if (current == NULL)
		cmd->env->tail = current;
	else
	{
		if (current->next == NULL)
			cmd->env->tail = current;
	}
}

/*
	Generic removal from env list
	with if statement for the tail
*/
static void	remove_from_list(t_commandlist *cmd, int key_place)
{
	t_envlist	*current;
	t_envlist	*to_remove;
	int			lc;

	current = cmd->env->head;
	to_remove = NULL;
	lc = 0;
	if (key_place == 0)
		replace_head(cmd);
	else
	{
		while (lc < key_place - 1)
		{
			lc++;
			current = current->next;
		}
		to_remove = current->next;
		current->next = to_remove->next;
		free(to_remove->key);
		if (to_remove->value != NULL)
			free(to_remove->value);
		free(to_remove);
		if (current->next == NULL)
			cmd->env->tail = current;
	}
}

/*
	unset, taking as many as possible
	there are no possible errors?
*/
void	ft_unset(t_commandlist *cmd, int update)
{
	int	lc;
	int	key_place;

	lc = 1;
	key_place = 0;
	while (cmd->cmd[lc] != NULL)
	{
		key_place = compare_to_list(cmd, cmd->cmd[lc]);
		if (key_place != -1)
		{
			remove_from_list(cmd, key_place);
			cmd->env->size = cmd->env->size - 1;
		}
		lc++;
	}
	clean_exit(update, cmd);
}
