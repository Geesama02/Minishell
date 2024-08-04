/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:34:39 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/04 15:46:33 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

void	caseof_long_error(t_token_tree *tree, char **cmds, char *path)
{
	char	current_dir[PATH_MAX];
	char	*pwd_value;
	char	*n_pwd;

	if (search_for_env(tree->head, "PWD"))
	{
		update_oldpwd(search_for_env(tree->head, "PWD")->env_val,
			cmds, tree);
		pwd_value = search_for_env(tree->head, "PWD")->env_val;
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
	long_error();
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

int	shlvl_negative_and_null_case(t_env_vars *shlvl, t_env_vars **head)
{
	if (shlvl->env_val && shlvl->env_val[0] == '-')
	{
		free(shlvl->env_val);
		shlvl->env_val = ft_strdup("0");
		if (!shlvl->env_val && errno == ENOMEM)
			return (free_envs(head), exit(1), -1);
		return (1);
	}
	if (!shlvl->env_val)
	{
		free(shlvl->env_val);
		shlvl->env_val = ft_strdup("1");
		if (!shlvl->env_val && errno == ENOMEM)
			return (free_envs(head), exit(1), -1);
		return (1);
	}
	return (0);
}

void	shlvl_cases(t_env_vars *shlvl, t_env_vars **head)
{
	int	shlvl_num;

	if (shlvl_negative_and_null_case(shlvl, head) == 1)
		return ;
	shlvl_num = ft_atoi(shlvl->env_val);
	if (shlvl_num >= 999)
	{
		free(shlvl->env_val);
		shlvl->env_val = ft_strdup("");
		if (!shlvl->env_val && errno == ENOMEM)
			return (free_envs(head), exit(1));
		return ;
	}
	else
		shlvl_num++;
	free(shlvl->env_val);
	shlvl->env_val = ft_itoa(shlvl_num);
	if (!shlvl->env_val && errno == ENOMEM)
		return (free_envs(head), exit(1));
}
