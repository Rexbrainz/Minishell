/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:43:05 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/28 15:53:07 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_g_buffer(char *getline_buffer, char *read_buffer);
char	*get_line_and_resize(char **fetchline_buffer);
char	*the_remaining(char **getline_buffer, ssize_t *index);
char	*resize(char **getline_buffer, char **line, size_t *index);
/*
int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int fd = open(argv[1], O_RDONLY, 0);
	char *line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
//	free(line);
	//while (line)
	//line = get_next_line(fd);
//	printf("%s", line);
//	free(line);
	//{
	//	printf("%s\n", line);
//	line = get_next_line(fd);
	//printf("%s", line);
//	free(line);
	//	free(line);
	//	line = get_next_line(fd);
//	line = get_next_line(fd);
//	printf("%s", line);
//	free(line);
	//}
	return (0);
}
*/

char	*get_next_line(int fd)
{
	static char	*getline_buffer = NULL;
	char		read_buffer[BUFFER_SIZE + 1];
	ssize_t		num_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!getline_buffer || !find_first_c(getline_buffer, '\n'))
	{
		num_bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (num_bytes > 0)
		{
			read_buffer[num_bytes] = '\0';
			getline_buffer = check_g_buffer(getline_buffer, read_buffer);
			if (!getline_buffer)
				return (the_remaining(&getline_buffer, &num_bytes));
		}
		else if (num_bytes == 0 && getline_buffer && *getline_buffer)
			return (the_remaining(&getline_buffer, &num_bytes));
		else
			return (the_remaining(&getline_buffer, &num_bytes));
	}
	return (get_line_and_resize(&getline_buffer));
}

char	*check_g_buffer(char *getline_buffer, char *read_buffer)
{
	char	*temp_buffer;

	if (!read_buffer)
		return (NULL);
	if (!getline_buffer)
		getline_buffer = duplicate(read_buffer);
	else if (getline_buffer)
	{
		temp_buffer = join(getline_buffer, read_buffer);
		if (!temp_buffer)
		{
			free(getline_buffer);
			getline_buffer = NULL;
			return (NULL);
		}
		free(getline_buffer);
		getline_buffer = NULL;
		getline_buffer = temp_buffer;
		temp_buffer = NULL;
	}
	return (getline_buffer);
}

char	*the_remaining(char **getline_buffer, ssize_t *num_bytes)
{
	char	*the_rest;

	if (!num_bytes || *num_bytes == -1 || !*getline_buffer || !**getline_buffer)
	{
		free(*getline_buffer);
		*getline_buffer = NULL;
		return (NULL);
	}
	the_rest = duplicate(*getline_buffer);
	if (!the_rest)
	{
		free(*getline_buffer);
		*getline_buffer = NULL;
		return (NULL);
	}
	free(*getline_buffer);
	*getline_buffer = NULL;
	return (the_rest);
}

char	*get_line_and_resize(char **getline_buffer)
{
	char	*line;
	char	*temp_buffer;
	char	*found;
	size_t	index;

	if (!getline_buffer || !*getline_buffer || !**getline_buffer)
		return (NULL);
	found = find_first_c(*getline_buffer, '\n');
	index = ++found - *getline_buffer;
	line = (char *) malloc(index + 1);
	if (!line)
		return (NULL);
	line = fetch_line(line, *getline_buffer, index + 1);
	if (*found)
	{
		temp_buffer = resize(getline_buffer, &line, &index);
		if (!temp_buffer)
			return (NULL);
	}
	else
		temp_buffer = NULL;
	free(*getline_buffer);
	*getline_buffer = temp_buffer;
	return (line);
}

char	*resize(char **getline_buffer, char **line, size_t *index)
{
	char	*temp;

	if (!index || !getline_buffer || !*getline_buffer || !line || !*line)
		return (NULL);
	temp = duplicate(*getline_buffer + *index);
	if (!temp)
	{
		free(*line);
		return (NULL);
	}
	free(*getline_buffer);
	*getline_buffer = NULL;
	return (temp);
}
