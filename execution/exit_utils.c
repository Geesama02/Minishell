/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:48:41 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/12 14:40:57 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	check_exit_argument(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '+' && arg[i + 1] == '+')
			|| (arg[i] == '-' && arg[i + 1] == '-')
			|| (arg[i] < '0' && i != 0)
			|| (arg[i] > '9' && i != 0))
			return (-1);
		i++;
	}
	return (0);
}

int	check_overflow_multiple_arguments(long exit_s, char **cmds)
{
	if (cmds[1][0] && !check_zeros(cmds[1]))
		exit(0);
	if (((exit_s == 0 || exit_s == -1)
			&& (ft_strcmp(cmds[1], "0")))
		|| (check_exit_argument(cmds[1]) == -1))
	{
		print_err("minishell: exit: ", cmds[1],
			": numeric argument required\n");
		exit(255);
	}
	else if (!check_exit_argument(cmds[1])
		&& count_2d_array_elements(cmds) > 2)
		return (print_err("minishell: exit: ",
				"too many arguments\n", NULL), -1);
	return (0);
}

int	check_zeros(char *number)
{
	int	i;

	i = 0;
	while (number[i])
	{
		if (number[i] != '0')
			return (-1);
		i++;
	}
	return (0);
}

void	get_first_cmd(char *holder)
{
	int	i;

	i = 0;
	while (holder[i] && (holder[i] != ' '
			|| (holder[i] == ' ' && is_inside_quotes(holder, i))))
		i++;
	holder[i] = '\0';
}

void	switch_tabs_to_spaces_nq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
