/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 06:44:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/11 08:21:59 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

volatile sig_atomic_t	g_sigint_detected = 0;

static void	disable_ctrlc_print(void)
{
	struct termios	new_setting;

	tcgetattr(STDIN_FILENO, &new_setting);
	new_setting.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_setting);
}

static void	handle_sigint(int signum)
{
	(void)signum;
	g_sigint_detected = 1;
}

void	reset_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	install_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_handler = handle_sigint;
	sigemptyset(&sig_int.sa_mask);
	sigaddset(&sig_int.sa_mask, SIGINT);
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
	sigaction(SIGINT, &sig_int, NULL);
	disable_ctrlc_print();
}
