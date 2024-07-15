/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:19:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/14 18:24:11 by maglagal         ###   ########.fr       */
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
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = dup(1);
	stdin_fd = dup(0);
	pipe(fds);
	dup2(fds[1], 1);
	dup2(fds[0], 0);
	write_to_pipe(content);
	dup2(stdout_fd, 1);
	close(stdout_fd);
	close(fds[1]);
	execute_tree(cmd, cmd->head, 1);
	dup2(stdin_fd, 0);
	close(stdin_fd);
	close(fds[0]);
}

void    execute_heredoc(t_token_tree *cmd, t_token_tree *content)
{	
	int			i;
	int			dir_or_file;
	char		**cmds;
	struct stat	ss;

	i = 0;
	dir_or_file = 0;
	cmds = ft_split(content->token, ' ');
	if (!cmds)
		return (free_tree(cmd), free_tree(content), exit(1));
	while (cmds[i])
	{
		stat(cmds[i], &ss);
		if (S_ISREG(ss.st_mode) || S_ISDIR(ss.st_mode))
			dir_or_file = 1;
		i++;
	}
	if (content->token || dir_or_file)
		execute_heredoc_file(cmd, content);
	else
		execute_heredoc_content(content, cmd);
}
