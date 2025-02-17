/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_table_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:55 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/17 14:14:56 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	should_exit(int update, t_commandlist *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (update == NO_REDIRECTION)
	{
		exit_status = cmd->env->exit_status;
		free_env_list(cmd->env);
		rl_clear_history();
		bin_malloc(-1);
		exit(exit_status);
	}
}

static int	handling_number_or_not(t_commandlist *cmd, int update)
{
	int	cc;

	cc = 0;
	while (cmd->cmd[1][cc] != '\0')
	{
		if (ft_isdigit(cmd->cmd[1][cc]) != 1)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[1], STDERR_FILENO);
			ft_putstr_fd(": numeric arguments required\n", STDERR_FILENO);
			cmd->env->exit_status = 255;
			return (should_exit(NO_REDIRECTION, cmd), 255);
		}
		cc++;
	}
	cmd->env->exit_status = ft_atoi(cmd->cmd[1]);
	return (should_exit(update, cmd), cmd->env->exit_status);
}

int	ft_exit(t_commandlist *cmd, int update)
{
	should_we_print(update);
	if (cmd->cmd[1] != NULL)
	{
		if (cmd->cmd[2] != NULL)
		{
			should_we_print(update);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd("to many arguments\n", STDERR_FILENO);
			cmd->env->exit_status = 1;
			return (cmd->env->exit_status);
		}
		else
			return (handling_number_or_not(cmd, update));
	}
	else
	{
		should_we_print(update);
		clean_exit(NO_REDIRECTION, cmd);
	}
	return (0);
}
