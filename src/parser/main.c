/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/31 08:03:57 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
//#include "scanner.h"

static void	prompt(t_tokens *tokens)
{
	tokens->t_input = readline("minishell$ ");
	if (!tokens->t_input)
		return ;
}

char	*prompt1(t_tokens *tokens)
{
	char	*more_input;
	char	*temp;
	int		len;

	more_input = readline("> ");
	if (!more_input)
		return (NULL);
	len = ft_strlen(tokens->t_input);
	temp = (char *)malloc (len + 1);
	if (!temp)
	{
		free(more_input);
		return (NULL);
	}
	ft_strlcpy(temp, tokens->t_input, len + 1);
	temp[len] = '\n';
	temp[len + 1] = '\0';
	free(tokens->t_input);
	tokens->t_input = ft_strjoin(temp, more_input);
	free(more_input);
	free(temp);
	return (tokens->t_input);
}

int	main(int argc, char **argv, char **env)
{
	int				i;
	t_command		cmd;
	t_commandlist	*current;
	t_tokens		tokens;
	t_toklist		*curr;

	(void)argv;
	(void)argc;
	(void)env;
	init_tokens(&tokens);
	init_commands(&cmd);
	while (1)
	{
		prompt(&tokens);
		if (!tokens.t_input)
			break ;
		add_history(tokens.t_input);
		parse_line(&cmd, &tokens);
		ft_printf("t_input-> [%s]\tLexeme count-> [%d]\n\n",
			tokens.t_input, tokens.lexeme_count);
		while (tokens.head)
		{
			ft_printf("lexeme-> [%s]\ttype-> [%d]\tPos-> [%d]\t\n",
				tokens.head->lexeme, tokens.head->type, tokens.head->start_pos);
			curr = tokens.head;
			tokens.head = tokens.head->next;
			free(curr->lexeme);
			free(curr);
		}
		free(tokens.t_input);
		current = cmd.head;
		while (cmd.head)
		{
			i = 0;
			ft_printf("Node type: [%d]\t", cmd.head->type);
			ft_printf("The command and arguments are: ");
			if (!cmd.head->cmd)
				ft_printf("NULL");
			else
				while (*(cmd.head->cmd))
					ft_printf("%d. [%s] ", i++, *(cmd.head->cmd)++);
			ft_printf("\n");
			if (cmd.head->files)
			{
				int j = 0;
				ft_printf("FILES\n");
				while (cmd.head->files->head)
				{
					ft_printf("FILE[%d]-> %s\n", j++, cmd.head->files->head->filename);
					cmd.head->files->head = cmd.head->files->head->next;
				}
			}
			current = cmd.head;
			cmd.head = cmd.head->next;
			free(current);
		}
	}
	return (0);
}
