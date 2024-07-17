/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:19:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/17 14:17:08 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	execute_heredoc_file(t_token_tree *cmd, t_token_tree *content)
{
	cmd->token = ft_strjoin(cmd->token, content->token);
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
	if (content->type == CMD_T)
		execute_heredoc_file(cmd, content);
	else
		execute_heredoc_content(content, cmd);
}
