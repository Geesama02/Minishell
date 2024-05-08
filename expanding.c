#include "parse_header.h"

void    print_env_variable(int j, char **tokens, t_env_vars **env_vars)
{
    int	i;
    char *env_n = NULL;

	env_n = NULL;
    i = 0;
    env_n = ft_strtrim(remove__quotes(tokens[j + 1]), "$");
    while (ft_strcmp(env_vars[i]->env_name, env_n))
        i++;
    printf("%s\n", env_vars[i]->env_val);
}
