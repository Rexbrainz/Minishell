/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:22:48 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/17 09:07:24 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
  			tokens->head->lexeme, tokens->head->type, 
			 tokens->head->start_pos, tokens->head->end_pos);
  		tokens->head = tokens->head->next;
 	}
 }
 */
/* for test minishell with mstest
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
/*
	Generaly what we used to see whats going on:
	parse_tokens(&cmd, &tokens, &en);
	tokens_print(&tokens);
	free_tokens_list(&tokens);
	commands_print(&cmd);
	free_cmds_list(&cmd);
*/

/**********************************************
 * 	Takes the tokens and command strucs.      *
 * 	Initializes the tokens and cmd structs.   *
 *	Prompts the user for input to process.    *
 *	Returns nothing.						  *
 *********************************************/
static void	prompt(t_tokens *tokens, t_command *cmd)
{
	init_tokens(tokens);
	init_commands(cmd);
	tokens->t_input = readline("minishell$ ");
}

/*****************************************************************
 * Takes the tokens struct, to access the existin current input  *
 * Asks the user for more prompts in conditions such as:         *
 * Unclosed quotes, \, |, && or || operator at the end of the    *
 * input entered. Adds a newline character to the existing input *
 * buffer before joining it with the newly entered input.        *
 * Returns the joined input strings.                             *
 *****************************************************************/
char	*prompt1(t_tokens *tokens)
{
	char	*more_input;
	char	*temp;
	int		len;

	more_input = readline("> ");
	if (!more_input || g_sigint_detected)
		return (g_sigint_detected = 0, NULL);
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

/*********************************************************
 * Called before exiting the program when ^D is entered. *
 * Takes the address of the exit_code to be returned and *
 * the environment symbol table struct. Frees the est    *
 * Sets the exit status. Clears history buffer.          *
 * The function returns nothing.                         *
 * *******************************************************/
static void	closing_state(int *exit_code, t_env *en)
{
	if (en->head != NULL)
		free_env_list(en);
	(*exit_code) = en->exit_status;
	rl_clear_history();
}

/************************************************************************
 * Takes the addresses of the cmd, tokens, env structs and exit code    *
 * The parser is called, and depending on it's return status            *
 * the executor is called. The exit status is colleceted                *
 * from the execute command which needs to be returned in case of       *
 * termination. Tokens list is freed after parsing or execution returns *
 * The function returns nothing.										*	
 * **********************************************************************/
static void	execution_body(t_command *cmd, t_tokens *tokens,
	t_env *en, int *exit_code)
{
	if (!parse_tokens(cmd, tokens, en))
	{
		free_tokens_list(tokens);
		(*exit_code) = execute_commands(cmd);
	}
	else
		free_tokens_list(tokens);
}

/*************************************************************
 * Initializes data structs, installs the main signal        *
 * and enters an infinite while loop, where it prompts for   *
 * input, processes and executes it.                         *
 * Returns an exit code upon termination.                    *
 * ***********************************************************/
int	main(int argc, char **argv, char **env)
{
	t_env		en;
	t_command	cmd;
	t_tokens	tokens;
	int			exit_code;

	exit_code = 0;
	init_env(&en, env, argv, argc);
	install_signals();
	while (1)
	{
		prompt(&tokens, &cmd);
		if (!tokens.t_input)
			break ;
		if (g_sigint_detected == 1)
		{
			en.exit_status = 1;
			g_sigint_detected = 0;
		}
		execution_body(&cmd, &tokens, &en, &exit_code);
		add_history(tokens.t_input);
		bin_malloc(-1);
	}
	closing_state(&exit_code, &en);
	return (exit_code);
}
