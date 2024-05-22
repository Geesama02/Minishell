/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:11:11 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/22 16:16:32 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

int	check_last_chars(struct dirent *dir_content, char **sep_str, char *str, int i)
{
	return (sep_str[i] == NULL && (str[ft_strlen(str) - 1] == '*'
			|| ft_strncmp(sep_str[i - 1], dir_content->d_name
			+ ((ft_strlen(dir_content->d_name))
			- (ft_strlen(sep_str[i - 1]))), ft_strlen(sep_str[i - 1])) == 0));
}

int check_first_chars(struct dirent *dir_content, char **sep_str, char *str, int i)
{
	return (sep_str[i] == NULL
			|| (ft_strncmp(sep_str[0], dir_content->d_name, ft_strlen(sep_str[0])) != 0
			&& str[0] != '*'));
}

int	filter_files(struct dirent *dir_content, char **sep_str, char *str, char **res)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(dir_content->d_name[j])
	{
		if (check_last_chars(dir_content, sep_str, str, i))
		{
			if (!join_strings(res, dir_content->d_name) || !join_strings(res, " "))
				return (free_2d_array(sep_str), rl_clear_history(), exit(1), 0);
			break;
		}
		else if (check_first_chars(dir_content, sep_str, str, i))
			break;
		else if (ft_strncmp(sep_str[i], dir_content->d_name + j, ft_strlen(sep_str[i])) == 0)
			j += ft_strlen(sep_str[i++]);
		else
			j++;
	}
	if (sep_str[i] == NULL && dir_content->d_name[j] == '\0'
		&& (!join_strings(res, dir_content->d_name)
		|| !join_strings(res, " ")))
			return (free_2d_array(sep_str), rl_clear_history(), exit(1), 0);
	return (1);
}