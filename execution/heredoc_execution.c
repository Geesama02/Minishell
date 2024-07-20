/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:19:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/19 12:24:26 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	add_space_cmd(t_token_tree *cmd)
{
	char	*token;
	int		len;
	int		i;

	i = 0;
	token = ft_strdup(cmd->token);
	if (!token)
		return (-1);
	len = ft_strlen(cmd->token);
	if (len >= 0 && cmd->token[len] != ' ')
	{	
		free(cmd->token);
		cmd->token = malloc((sizeof(char) * ft_strlen(token)) + 2);
		if (!cmd->token)
			return (-1);
		while (token[i])
		{
			cmd->token[i] = token[i];
			i++;
		}
		cmd->token[i] = ' ';
		cmd->token[i + 1] = '\0';
	}
	free(token);
	return (0);
}

void	execute_heredoc_file(t_token_tree *cmd, t_token_tree *content)
{
	char *prev_cmd;

	prev_cmd = cmd->token;
	cmd->token = ft_strjoin(prev_cmd, content->token);
	free(prev_cmd);
	if (!cmd->token)
		return (free_tree(cmd), free_tree(content), exit(1));
	execute_tree(cmd, cmd->head, 1);
}

void	write_to_pipe(t_token_tree *content)
{
	int	i;

	i = 0;
	while (content->token[i])
	{
		write(1, &content->token[i], 1);
		i++;
	}
}

void	execute_heredoc_content(t_token_tree *content, t_token_tree *cmd)
{
	int		fds[2];
	int		stdout_cp;
	int		stdin_cp;

	stdout_cp = dup(1);
	stdin_cp = dup(0);
	pipe(fds);
	dup2(fds[1], 1);
	close(fds[1]);
	write_to_pipe(content);
	dup2(stdout_cp, 1);
	close(stdout_cp);
	dup2(fds[0], 0);
	close(fds[0]);
	execute_tree(cmd, cmd->head, 1);
	dup2(stdin_cp, 0);
	close(stdin_cp);
}

void    execute_heredoc(t_token_tree *cmd, t_token_tree *content)
{
	if (add_space_cmd(cmd) == -1)
		return (free_tree(cmd), free_tree(content),
			free_envs(cmd->head), exit(1));
	if (content->type == CMD_T)
		execute_heredoc_file(cmd, content);
	else
		execute_heredoc_content(content, cmd);
}
