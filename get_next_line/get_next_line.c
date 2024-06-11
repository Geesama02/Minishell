/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/06/11 10:03:43 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*freeing_memory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*make_line(char **buffer, char **next_buffer, char **r_buffer)
{
	char	*line;

	line = ft_strdup(*buffer);
	if (!line)
	{
		freeing_memory(r_buffer);
		freeing_memory(next_buffer);
		return (freeing_memory(buffer));
	}
	freeing_memory(buffer);
	if (*next_buffer && *next_buffer[0] != '\0')
	{
		*buffer = ft_strdup(*next_buffer);
		if (!*buffer)
		{
			freeing_memory(next_buffer);
			freeing_memory(r_buffer);
			return (freeing_memory(&line));
		}
		freeing_memory(next_buffer);
	}
	freeing_memory(r_buffer);
	return (line);
}

static char	*making_buffer(char **buffer, char **r_buffer, int nbytes)
{
	char	*temp_buffer;

	*(*r_buffer + nbytes) = '\0';
	if (*buffer == NULL)
	{
		*buffer = ft_strdup(*r_buffer);
		if (!*buffer)
			return (freeing_memory(r_buffer));
	}
	else
	{
		temp_buffer = *buffer;
		*buffer = ft_strjoin(temp_buffer, *r_buffer);
		if (!*buffer)
		{
			freeing_memory(&temp_buffer);
			return (freeing_memory(r_buffer));
		}
		freeing_memory(&temp_buffer);
	}
	return (*buffer);
}

static char	*check_newline(char **buffer, char **r_buffer, char **line_rest)
{
	char	*check_nl;

	check_nl = ft_strchr(*buffer, '\n');
	if (check_nl != NULL)
	{
		check_nl++;
		if (*check_nl != '\0')
		{
			*line_rest = ft_strdup(check_nl);
			if (!*line_rest)
			{
				freeing_memory(r_buffer);
				return (freeing_memory(buffer));
			}
		}
		terminating_string(*buffer);
	}
	return (check_nl);
}

char	*get_next_line(int fd)
{
	int			nbytes;
	static char	*buffer;
	char		*r_buffer;
	char		*line_rest;

	line_rest = NULL;
	r_buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (fd < 0 || fd > OPEN_MAX || !r_buffer || read(fd, "", 0) < 0)
	{
		freeing_memory(&buffer);
		return (freeing_memory(&r_buffer));
	}
	nbytes = read(fd, r_buffer, BUFFER_SIZE);
	while (nbytes > 0 || (buffer && ft_strchr(buffer, '\n')))
	{
		making_buffer(&buffer, &r_buffer, nbytes);
		if (buffer && check_newline(&buffer, &r_buffer, &line_rest))
			return (make_line(&buffer, &line_rest, &r_buffer));
		nbytes = read(fd, r_buffer, BUFFER_SIZE);
	}
	freeing_memory(&r_buffer);
	if (buffer && nbytes == 0)
		return (make_line(&buffer, &line_rest, &r_buffer));
	return (freeing_memory(&buffer));
}
