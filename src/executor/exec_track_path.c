/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_track_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:53:48 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/13 14:53:49 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*
	Keeping the memory safe
	called before returning
*/
static void	cleaning(char **parts)
{
	int	i;

	i = 0;
	if (parts == NULL)
		return ;
	while (parts[i] != NULL)
	{
		free(parts[i]);
		i++;
	}
	free(parts);
	parts = NULL;
}

/*
	Look through smaller parts of path
	checking for option to exectute
	till we find or check everything
*/
static char	*find_command(char *av, char **parts)
{
	char	*tmp;
	char	*path;
	int		loop;

	loop = 0;
	path = NULL;
	tmp = NULL;
	while (parts[loop] != NULL)
	{
		tmp = ft_strjoin(parts[loop], "/");
		if (tmp == NULL)
			return (NULL);
		path = ft_strjoin(tmp, av);
		if (path == NULL)
			return (free(tmp), NULL);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		loop++;
	}
	return (path);
}

/*
	looking for the PATH in the env variable
	returning it (if found) for later use
*/
char	*find_path(char *av, char **en)
{
	char	**parts;
	char	*path;
	int		loop;

	loop = 0;
	path = NULL;
	parts = NULL;
	while (en[loop] != NULL)
	{
		if (ft_strncmp(en[loop], "PATH=", 5) == 0)
		{
			parts = ft_split(en[loop] + 5, ':');
			if (parts == NULL)
				return (NULL);
			break ;
		}
		loop++;
	}
	if (parts != NULL)
	{
		path = find_command(av, parts);
		cleaning(parts);
	}
	return (path);
}
