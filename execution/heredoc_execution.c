/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:19:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/03 10:50:09 by oait-laa         ###   ########.fr       */
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

void	execute_heredoc_file(t_token_tree *tree, t_token_tree *cmd,
	t_token_tree *content)
{
	char	*prev_cmd;

	prev_cmd = cmd->token;
	cmd->token = ft_strjoin(prev_cmd, content->token);
	free(prev_cmd);
	if (!cmd->token)
		return (ft_close(NULL, tree->head, tree), exit(1));
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

void	execute_heredoc_content(t_token_tree *tree, t_token_tree *cmd,
	t_token_tree *content)
{
	int		fds[2];
	int		stdout_cp;
	int		stdin_cp;

	stdout_cp = safe_dup(1, tree);
	stdin_cp = safe_dup(0, tree);
	if (pipe(fds) == -1)
		return (print_err("minishell: ", strerror(errno), "\n"),
			ft_close(NULL, tree->head, tree));
	safe_dup2(tree, fds[1], 1);
	safe_close(fds[1], tree);
	write_to_pipe(content);
	safe_dup2(tree, stdout_cp, 1);
	safe_close(stdout_cp, tree);
	safe_dup2(tree, fds[0], 0);
	safe_close(fds[0], tree);
	if (cmd->token[0])
		execute_tree(cmd, cmd->head, 1);
	safe_dup2(tree, stdin_cp, 0);
	safe_close(stdin_cp, tree);
}

void	execute_heredoc(t_token_tree *tree)
{
	if (tree->left->token[0] && add_space_cmd(tree->left) == -1)
		return (free_tree(tree), exit(1));
	if (tree->right->type == CMD_T)
		execute_heredoc_file(tree, tree->left, tree->right);
	else
		execute_heredoc_content(tree, tree->left, tree->right);
}
