/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_failure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:32:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/16 14:27:56 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    print_err(char *string1, char *string2, char *string3)
{
    ft_putstr_fd(string1, 2);
    ft_putstr_fd(string2, 2);
    ft_putstr_fd(string3, 2);
}
