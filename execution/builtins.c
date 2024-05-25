#include "../parse_header.h"

int cd_command(char *path)
{
	if (!path || (path && !ft_strcmp(path, "~")))
	{
		if (chdir(getenv("HOME")) != 0)
		{
			write(2, "chdir() failed!!\n", 18);
			return (-1);
		}
	}
	else if (chdir(path) != 0)
	{
		write(2, "chdir() failed!!\n", 18);
		return (-1);
	}
	return (0);
}

int pwd_command()
{
	char buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff)))
	{
		write(2, "getcwd() failed!!\n", 19);
		return (-1);
	}
	else
	{    
		write(1, buff, ft_strlen(buff));
		write(1, "\n", 1);
	}
	return (0);
}

int echo_command(char *string)
{
	if (!string)
	{
		write(1, "\n", 1);
		write(1, "\n", 1);
	}
	while (*string && *string != '>')
	{
		if (write(1, &*string, 1) == -1)
			return (-1);
		string++;
	}
	return (0);
}

t_env_vars  *export_command(char **tokens, t_env_vars *head, char **envp)
{
	int			nbr_envs;

	if (!tokens[1])
		export_without_arguments(head, envp);
	nbr_envs = count_env_vars(tokens);
	head = add_env_var(tokens, nbr_envs, head);
	return (head);
}

void    unset_command(t_env_vars **head, char *cmd)
{
	t_env_vars *tmp;

	tmp = *head;
	if (tmp && !ft_strcmp(tmp->env_name, cmd))
	{    
		tmp->env_name = NULL;
		tmp->env_val = NULL;
		if (tmp->next)
			*head = tmp->next;
		else
			*head = NULL;
		free(tmp);
	}
	else
	{
		while (tmp && tmp->next && ft_strcmp(tmp->next->env_name, cmd))
			tmp = tmp->next;
		if (tmp && tmp->next && tmp->next->next)
			tmp->next = tmp->next->next;
		else
			tmp->next = NULL;
		free(tmp->next);
	}
}

void    env_command(t_env_vars *env_vars, char **envp)
{
	while (*envp)
	{
		while (*envp)
		{    
			printf("%s\n", *envp);
			envp++;
		}
	}
	while (env_vars && env_vars->env_val)
	{
		printf("%s=%s\n", env_vars->env_name, env_vars->env_val);
		env_vars = env_vars->next;
	}
}

