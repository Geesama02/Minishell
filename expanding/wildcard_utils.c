/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:59:18 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/22 19:56:03 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	join_strings(char **s1, char *s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	if (!*s1)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int	handle_hidden_files(DIR *dir, struct dirent **dir_content, char **sep_str, char *str)
{
	if (ft_strncmp((*dir_content)->d_name, ".", 2) == 0
		|| ft_strncmp((*dir_content)->d_name, "..", 3) == 0
		|| ((*dir_content)->d_name[0] == '.'
		&& (sep_str[0] == NULL || str[0] != '.')))
	{
		*dir_content = readdir(dir);
		return (1);
	}
	return (0);
}

char *wildcard(char *str)
{
	DIR *dir;
	struct dirent *dir_content;
	char **sep_str;
	char *res;
	
	res = ft_strdup("");
	sep_str = ft_split(str, '*');
	if (!sep_str)
		return (free(res), exit(1), NULL);
	dir = opendir(".");
	if (!dir)
		return (free_2d_array(sep_str), free(res), exit(1), NULL);
	dir_content = readdir(dir);
	while (dir_content != NULL)
	{
		if (handle_hidden_files(dir, &dir_content, sep_str, str))
			continue;
		filter_files(dir_content, sep_str, str, &res);
		dir_content = readdir(dir);
	}
	free_2d_array(sep_str);
	closedir(dir);
	if (ft_strcmp(res, "") == 0)
		write_error("No matches found\n");
	return (res);
}

int	join_wildcard(char **sep_str, char **str)
{
	int i;
	char *wildcard_holder;
	
	i = 0;
	while (sep_str[i])
	{
		if (has_wildcard(sep_str[i]))
		{
			wildcard_holder = wildcard(sep_str[i]);
			if (wildcard_holder && *wildcard_holder == '\0')
				return (free(wildcard_holder), free_2d_array(sep_str));
			if (!wildcard_holder || !join_strings(str, wildcard_holder)
				|| !join_strings(str, " "))
				return (free_2d_array(sep_str), exit(1), 0);
			free(wildcard_holder);
		}
		else
		{
			if (!join_strings(str, sep_str[i]) || !join_strings(str, " "))
				return (free_2d_array(sep_str), exit(1), 0);
		}
		i++;
	}
	return (1);
}
