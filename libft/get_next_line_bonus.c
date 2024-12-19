/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:25:57 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/28 15:48:15 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_buffer(char *buffer, char *read_file);
char	*get_line_and_update(char **buffer);
char	*resize(char **buffer, char **line, size_t *index);
char	*the_rest(char **buffer, ssize_t *index);
/*
int	main(int argc, char **argv)
{
	int fd;
	int fd1;
	if (argc < 3)
		return (0);
	fd = open(argv[1], O_RDONLY);
	fd1 = open(argv[2], O_RDONLY);
	char *line = get_next_line(fd);

	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd1);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		line = get_next_line(fd);
	}
	close(fd);
	close(fd1);
	return (0);
}
*/

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	ssize_t		num_bytes;
	char		read_file[BUFFER_SIZE + 1];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!buffer[fd] || !find_first_c(buffer[fd], '\n'))
	{
		num_bytes = read(fd, read_file, BUFFER_SIZE);
		if (num_bytes > 0)
		{
			read_file[num_bytes] = '\0';
			buffer[fd] = check_buffer(buffer[fd], read_file);
			if (!buffer[fd])
				return (free(buffer[fd]), NULL);
		}
		else if (num_bytes == 0 && buffer[fd] && *buffer[fd])
			return (the_rest(&buffer[fd], &num_bytes));
		else
			return (the_rest(&buffer[fd], &num_bytes));
	}
	return (get_line_and_update(&buffer[fd]));
}

char	*check_buffer(char *buffer, char *read_file)
{
	char	*temp_buffer;

	if (!read_file)
		return (NULL);
	if (!buffer)
		buffer = duplicate(read_file);
	else if (buffer)
	{
		temp_buffer = join(buffer, read_file);
		if (!temp_buffer)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		free(buffer);
		buffer = NULL;
		buffer = temp_buffer;
		temp_buffer = NULL;
	}
	return (buffer);
}

char	*get_line_and_update(char **buffer)
{
	char	*line;
	char	*found;
	char	*temp;
	size_t	index;

	if (!buffer || !*buffer || !**buffer)
		return (NULL);
	found = find_first_c(*buffer, '\n');
	index = ++found - *buffer;
	line = (char *)malloc(index + 1);
	if (!line)
		return (NULL);
	line = fetch_line(line, *buffer, index + 1);
	if (*found)
	{
		temp = resize(buffer, &line, &index);
		if (!temp)
			return (NULL);
	}
	else
		temp = NULL;
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*resize(char **buffer, char **line, size_t *index)
{
	char	*temp;

	if (!buffer || !*buffer || !line || !*line || !*index)
		return (NULL);
	temp = duplicate(*buffer + *index);
	if (!temp)
	{
		free(*line);
		return (NULL);
	}
	free(*buffer);
	*buffer = NULL;
	return (temp);
}

char	*the_rest(char **buffer, ssize_t *num_bytes)
{
	char	*the_rest;

	if (!buffer || !*buffer || !**buffer || !num_bytes || *num_bytes == -1)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	the_rest = duplicate(*buffer);
	if (!the_rest)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	free(*buffer);
	*buffer = NULL;
	return (the_rest);
}
