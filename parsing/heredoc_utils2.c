/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:29:02 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/08 15:28:26 by oait-laa         ###   ########.fr       */
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

	input = ft_strdup("");
	if (!input)
		return (NULL);
	while (1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
			return (handle_null(input));
		if (tmp[0] == '\0')
		{
			if (!handle_empty_line(&input, input, tmp))
				return (NULL);
			else
				continue ;
		}
		if (ft_strcmp(tmp, delimiter) == 0)
			return (free(tmp), input);
		if (!join_old_to_new(&input, tmp))
			return (NULL);
	}
	return (input);
}

void	check_if_has_file(t_token_array *token_array, char **token,
	t_token_vars *vars, char *tmp)
{
	if (vars->check)
	{
		free(*token);
		if (vars->cmd_holder)
			*token = ft_strdup(vars->cmd_holder);
		else
			*token = ft_strdup(tmp);
		token_array[vars->x].type = CMD_T;
	}
	else
		token_array[vars->x].type = HEREDOC_TOKEN;
}
