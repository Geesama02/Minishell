/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:34:39 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/04 11:47:00 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

void    caseof_long_error(t_token_tree *tree, char **cmds, char *path)
{
	char    current_dir[PATH_MAX];
	char    *pwd_value;
	char    *n_pwd;

	if (search_for_env_var(tree->head, "PWD"))
	{
		update_oldpwd(search_for_env_var(tree->head, "PWD")->env_val, cmds, tree);
		pwd_value = search_for_env_var(tree->head, "PWD")->env_val;
		if (!ft_strcmp(path, "."))
			n_pwd = ft_strjoin(pwd_value, "/.");
		else
			n_pwd = ft_strjoin(pwd_value, "/..");
		if (!n_pwd && errno == ENOMEM)
			return (ft_close(cmds, tree->head, tree), free(path), exit(1));
		update_pwd(cmds, tree, n_pwd);
		free(n_pwd);
	}
	else
	{
		getcwd(current_dir, sizeof(current_dir)); 
		update_pwd(cmds, tree, current_dir);
	}
	print_err("cd: error retrieving current directory: getcwd: cannot access parent directories: ",
		strerror(errno), "\n");
}

int	check_space_only(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == ' ')
			i++;
		else
			return (-1);
	}
	return (0);
}

char	*ignore_first_last_quotes(char *string)
{
	int		i;
	int		j;
	char	*alloc_str;

	i = 0;
	j = 0;
	if (!string)
		return (NULL);
	alloc_str = malloc((sizeof(char) * ft_strlen(string)) - 1);
	if (string[i] && string[i] == '\"')
	{
		i++;
		while (string[i] && string[i] != '\"')
		{
			alloc_str[j] = string[i];
			j++;
			i++;
		}
	}
	alloc_str[j] = '\0';
	free(string);
	return (alloc_str);
}
