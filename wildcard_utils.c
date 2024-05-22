/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:59:18 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/22 09:39:33 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

char *wildcard(char *str)
{
	DIR *dir;
	struct dirent *dir_content;
	char **sep_str;
	
	sep_str = ft_split(str, '*');
	if (!sep_str)
		return (NULL);
	dir = opendir(".");
	dir_content = readdir(dir);
	while (dir_content != NULL)
	{
		int i = 0;
		int j = 0;

		while(dir_content->d_name[j])
		{
			if (sep_str[i] == NULL && (str[ft_strlen(str) - 1] == '*'
				|| ft_strncmp(sep_str[i - 1], dir_content->d_name
				+ ((ft_strlen(dir_content->d_name))
				- (ft_strlen(sep_str[i - 1]))), ft_strlen(sep_str[i - 1])) == 0))
			{
				printf("%s\n", dir_content->d_name);
				break;
			}
			else if (sep_str[i] == NULL)
				break;
			else if (ft_strncmp(sep_str[i], dir_content->d_name + j, ft_strlen(sep_str[i])) == 0)
			{
				j += ft_strlen(sep_str[i]);
				i++;
			}
			else if (ft_strncmp(sep_str[0], dir_content->d_name, ft_strlen(sep_str[0])) != 0 && str[0] != '*')
				break;
			else
				j++;
		}
		// printf("name -> %s | i %d | j %d\n", dir_content->d_name, i, j);÷
		// printf("%s\n", dir_content->d_name + ((ft_strlen(dir_content->d_name)) - (ft_strlen(sep_str[i - 1])));
		if (sep_str[i] == NULL && dir_content->d_name[j] == '\0')
			printf("%s\n", dir_content->d_name);
		dir_content = readdir(dir);
	}
	return (str);
}