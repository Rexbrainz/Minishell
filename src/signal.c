/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 06:44:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/17 10:17:02 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/*
 * global variable set for signal handling
 */
volatile sig_atomic_t	g_sigint_detected = 0;

/*
 * Disables the terminal's use of echo, upon receiving a signal
 */
static void	disable_ctrlc_print(void)
{
	struct termios	new_setting;

	tcgetattr(STDIN_FILENO, &new_setting);
	new_setting.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_setting);
}

/****************************************************************
 * Catches and handles SIGINT upon arrival.                     *
 * Sets the global variable upon catchin SIGINT, and resets the *
 * prompt on a newline.                                         *
 ****************************************************************/
void	main_sigint_handler(int signum)
{
	(void)signum;
	g_sigint_detected = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
 * Catches and handles SIGINT in the child process.
 */
void	child_sigint_handler(int signum)
{
	(void)signum;
	exit(130);
}

/*********************************************************************
 * Catches and handles SIGINT when in a new prompt mode,             *
 * excuse the name choice, it was firstly written for the heredoc    *
 * prompt, until I saw it could be reused for all prompt more        *
 * functions.                                                        *
 * rl_done set to 1 tells readline to stop and return, however,      *
 * readline does not return immediately, as it sets the cursor to    *
 * the start of the line. ioctl is very important in that it         *
 * interacts with the Standard input causing readline to return.     *
 * *******************************************************************/
void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_sigint_detected = 2;
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\t");
}

/*
 * Installs signal handlers for SIGINT and SIGQUIT
 */
void	install_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_handler = main_sigint_handler;
	sigemptyset(&sig_int.sa_mask);
	sigaddset(&sig_int.sa_mask, SIGINT);
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
	sigaction(SIGINT, &sig_int, NULL);
	disable_ctrlc_print();
}
