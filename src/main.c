
#include "../Includes/minishell.h"
//#include "scanner.h"
/*
 static void	commands_print(t_command *cmd)
 {
 	int				i;
 	int				j;
 	t_commandlist	*current;

 	current = cmd->head;
 	while (cmd->head)
 	{
 		i = 0;
 		ft_printf("Node type: [%d]\t", cmd->head->type);
 		if (!cmd->head->cmd)
 			ft_printf("PIPELINE SEPARATOR");
 		else
 		{
 			ft_printf("The command and arguments are: ");
 			while (*(cmd->head->cmd))
 				ft_printf("%d. [%s] ", i++, *(cmd->head->cmd)++);
 		}
 		ft_printf("\n");
 		if (cmd->head->files)
 		{
 			j = 0;
 			ft_printf("FILES\n");
 			while (cmd->head->files->head)
 			{
 				ft_printf("FILE[%d]-> %s\n", j++,
 					cmd->head->files->head->filename);
 				cmd->head->files->head = cmd->head->files->head->next;
 			}
 		}
 		current = cmd->head;
 		cmd->head = cmd->head->next;
 		free(current);
 	}
 }
*/
/*
static void	tokens_print(t_tokens *tokens)
{
  	ft_printf("t_input-> [%s]\tLexeme count-> [%d]\n\n",
  		tokens->t_input, tokens->lexeme_count);
  	while (tokens->head)
  	{
  		ft_printf("lexeme-> [%s]\ttype-> [%d]\tS_Pos-> [%d]\tE_Pos-> [%d]\n",
  			tokens->head->lexeme, tokens->head->type, tokens->head->start_pos, tokens->head->end_pos);
  		tokens->head = tokens->head->next;
 	}
 }
*/

/* for test minishell
	if (isatty(fileno(stdin)))
		tokens->t_input = readline("minishell$ ");
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		if (line == NULL)
			return ;
		tokens->t_input = ft_strtrim(line, "\n");
		free(line);
	}
*/
static void	prompt(t_tokens *tokens, t_command *cmd)
{
	init_tokens(tokens);
	init_commands(cmd);
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
	t_env			en;
	t_command		cmd;
	t_tokens		tokens;

	(void)argv;
	(void)argc;
	init_env(&en, env);
	install_signals();
	while (1)
	{
		if (g_sigint_detected == 1)
		{
			if (tokens.head)
				free_tokens_list(&tokens);
			if (cmd.head)
				bin_malloc(-1);
			en.exit_status = 1;
			g_sigint_detected = 0;
		}
		prompt(&tokens, &cmd);
		if (!tokens.t_input)
			break ;
//		 parse_tokens(&cmd, &tokens, &en);
		if (!parse_tokens(&cmd, &tokens, &en))
		{
			free_tokens_list(&tokens);
			execute_commands(&cmd);
		}
		else
			free_tokens_list(&tokens);
		add_history(tokens.t_input);
		//tokens_print(&tokens);
//		free_tokens_list(&tokens);
//		commands_print(&cmd);
	//	 free_cmds_list(&cmd);
		bin_malloc(-1);
	}
	free_env_list(&en);
	rl_clear_history();
	return (0);
}
