/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:29:02 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/12 13:55:08 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	join_old_to_new(char **input, char *tmp)
{
	char	*old_input;

	old_input = *input;
	*input = ft_strjoin(old_input, tmp);
	if (!*input)
		return (free(old_input), free(tmp), 0);
	free(old_input);
	free(tmp);
	old_input = *input;
	*input = ft_strjoin(old_input, "\n");
	if (!*input)
		return (free(old_input), 0);
	free(old_input);
	return (1);
}

int	handle_empty_line(char **input, char *input_cpy, char *tmp)
{
	char	*old_input;

	free(tmp);
	old_input = input_cpy;
	*input = ft_strjoin(old_input, "\n");
	if (!*input)
		return (free(old_input), 0);
	free(old_input);
	return (1);
}

char	*handle_null(char *input)
{
	if (errno == ENOMEM)
	{
		write_error("readline: allocation failure!");
		free(input);
		return (NULL);
	}
	else
		return (input);
}

char	*continue_heredoc(char *delimiter)
{
    char	*tmp;
	char	*input;
	int		stdin_fd;

	is_heredoc[0] = 1;
	stdin_fd = dup(0);
	input = ft_strdup("");
	if (!input)
		return (NULL);
    while (1)
	{
		tmp = readline("> ");
		if (is_heredoc[1])
		{
			dup2(stdin_fd, 0);
			close(stdin_fd);
			return (NULL);
		}
		if (tmp == NULL)
			return (handle_null(input));
		if (tmp[0] == '\0')
		{
			if (!handle_empty_line(&input, input, tmp))
			{
				dup2(stdin_fd, 0);
				close(stdin_fd);
				return (NULL);
			}
			else
				continue;
		}
		if (ft_strcmp(tmp, delimiter) == 0)
			return (free(tmp), input);
		if (!join_old_to_new(&input, tmp))
			return (NULL);
    }
	return (input);
}