/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:46:53 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/08 14:27:38 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

void	eof_pressed(t_env_vars **head)
{
	t_env_vars	*tmp;
	long		exit_s;

	exit_s = 0;
	tmp = search_for_env(head, "?");
	if (tmp)
		exit_s = ft_atoi_long(tmp->env_val);
	write(0, "exit\n", 5);
	ft_close(NULL, head, NULL);
	if (g_is_heredoc[1] == 1)
		exit(1);
	exit(exit_s);
}

char	*check_syntax(char *input)
{
	int	i;
	int	quote;
	int	dquote;
	int	parenthesis;

	i = 0;
	quote = 0;
	dquote = 0;
	parenthesis = 0;
	while (input[i])
	{
		if (input[i] == ')' && parenthesis == 0
			&& is_inside_quotes(input, i) == 0)
			return (")");
		if (input[i] == '(' && is_inside_quotes(input, i) == 0)
			parenthesis++;
		if (input[i] == ')' && is_inside_quotes(input, i) == 0)
			parenthesis--;
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	return (return_type(dquote, quote, parenthesis));
}

int	syntax_error_check(t_env_vars *head, char *input)
{
	if (check_syntax(input))
		return (add_history(input), syntax_error_message(head, input), -1);
	return (1);
}

void	syntax_error_message(t_env_vars *head, char *input)
{
	print_err("Minishell: syntax error near unexpected token `",
		check_syntax(input), "' \n");
	define_exit_status(head, "258");
	update_underscore_env(input, NULL, head, NULL);
}

void	readline_allocation_failure(t_env_vars *head)
{
	print_err("readline: allocation failure!\n", NULL, NULL);
	ft_close(NULL, &head, NULL);
	exit(1);
}
