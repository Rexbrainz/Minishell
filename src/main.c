
#include "../Includes/minishell.h"
//#include "scanner.h"

// static void	commands_print(t_command *cmd)
// {
// 	int				i;
// 	int				j;
// 	t_commandlist	*current;

// 	current = cmd->head;
// 	while (cmd->head)
// 	{
// 		i = 0;
// 		ft_printf("Node type: [%d]\t", cmd->head->type);
// 		if (!cmd->head->cmd)
// 			ft_printf("PIPELINE SEPARATOR");
// 		else
// 		{
// 			ft_printf("The command and arguments are: ");
// 			while (*(cmd->head->cmd))
// 				ft_printf("%d. [%s] ", i++, *(cmd->head->cmd)++);
// 		}
// 		ft_printf("\n");
// 		if (cmd->head->files)
// 		{
// 			j = 0;
// 			ft_printf("FILES\n");
// 			while (cmd->head->files->head)
// 			{
// 				ft_printf("FILE[%d]-> %s\n", j++,
// 					cmd->head->files->head->filename);
// 				cmd->head->files->head = cmd->head->files->head->next;
// 			}
// 		}
// 		current = cmd->head;
// 		cmd->head = cmd->head->next;
// 		free(current);
// 	}
// }

/*
 static void	tokens_print(t_tokens *tokens)
 {
 	ft_printf("t_input-> [%s]\tLexeme count-> [%d]\n\n",
 		tokens->t_input, tokens->lexeme_count);
 	while (tokens->head)
 	{
 		ft_printf("lexeme-> [%s]\ttype-> [%d]\tPos-> [%d]\t\n",
 			tokens->head->lexeme, tokens->head->type, tokens->head->start_pos);
 		tokens->head = tokens->head->next;
	}
}
*/

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
	t_command		cmd;
	t_tokens		tokens;

	(void)argv;
	(void)argc;
	while (1)
	{
		init_tokens(&tokens);
		init_commands(&cmd);
		prompt(&tokens);
		if (!tokens.t_input)
			break ;
		add_history(tokens.t_input);
		parse_tokens(&cmd, &tokens, env);
		// tokens_print(&tokens);
		free_tokens_list(&tokens);	
		run_tokens(&cmd);
		// commands_print(&cmd);
		// free_cmds_list(&cmd);
		bin_malloc(-1);
	}
	return (0);
}
