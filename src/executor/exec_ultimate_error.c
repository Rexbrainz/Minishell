#include "minishell.h"

/*
	General error message after checks
	- if no extra work is needed
*/
void	standard_error(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(errno);
}
