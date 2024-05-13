#include "parse_header.h"

int cd_command(char *path)
{
    if (!path || (path && !ft_strcmp(path, "~")))
    {
        if (chdir("/") != 0)
        {
            write(2, "chdir() failed!!\n", 18);
            return (-1);
        }
    }
    if (chdir(path) != 0)
    {
        perror("chdir");
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
        printf("%s\n", buff);
    return (0);
}

int echo_command(char *string)
{
    while (*string)
    {
        if (write(1, &*string, 1) == -1)
            return (-1);
        string++;
    }
    return (0);
}

t_env_vars  *export_command(char **tokens, t_env_vars *p_head)
{
    t_env_vars  *env_vars;
    t_env_vars  *prev;
    t_env_vars  *head;
    int         nbr_envs;
    int         i;
    char        **cmds;

    i = 1;
    env_vars = NULL;
    prev = NULL;
    head = NULL;
    if (p_head)
    {
        while (p_head->next)
            p_head = p_head->next;
    }
    nbr_envs = count_env_vars(tokens);
    while (i <= nbr_envs)
    {
        if (ft_strchr(tokens[i], '='))
        {
            cmds = ft_split(tokens[i], '=');
            env_vars = malloc(sizeof(t_env_vars));
            env_vars->env_name = cmds[0];
            env_vars->env_val = cmds[1];
            if (p_head && i == 1)
            {    
                p_head->next = env_vars;
                head = p_head;
            }
            else if (!p_head && i == 1)
                head = env_vars;
            env_vars->next = NULL;
            if (i != 1)
                prev->next = env_vars;
            prev = env_vars;
        }
        else
            printf("export: `%s' : not a valid identifier", tokens[i]);
        i++;
    }
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

void    env_command(char *env_name, t_env_vars *env_vars)
{
    char *env_n;
    char *env_res;

    env_n = NULL;
    env_res = NULL;
    if (env_name && ft_strchr(env_name, '$'))
        env_n = ft_strtrim(env_name, "$");
    else if (env_name && !ft_strchr(env_name, '$'))
        printf("env: %s: No such file or directory\n", env_name);
    env_res = getenv(env_n);
    if (env_res)
        printf("%s", env_res);
    else
    {
        printf("TERM_PROGRAM=%s\n", getenv("TERM_PROGRAM"));
        printf("SHELL=%s\n", getenv("SHELL"));
        printf("TERM=%s\n", getenv("TERM"));
        printf("TMPDIR=%s\n", getenv("TMPDIR"));
        printf("TERM_PROGRAM_VERSION=%s\n", getenv("TERM_PROGRAM_VERSION"));
        printf("ZDOTDIR=%s\n", getenv("ZDOTDIR"));
        printf("ORIGINAL_XDG_CURRENT_DESKTOP=%s\n", getenv("ORIGINAL_XDG_CURRENT_DESKTOP"));
        printf("TERM_SESSION_ID=%s\n", getenv("TERM_SESSION_ID"));
        printf("ZSH=%s\n", getenv("ZSH"));
        printf("USER=%s\n", getenv("USER"));
        printf("LS_COLORS=%s\n", getenv("LS_COLORS"));
        printf("COMMAND_MODE=%s\n", getenv("COMMAND_MODE"));
        printf("SSH_AUTH_SOCK=%s\n", getenv("SSH_AUTH_SOCK"));
        printf("__CF_USER_TEXT_ENCODING=%s\n", getenv("__CF_USER_TEXT_ENCODING"));
        printf("PAGER=%s\n", getenv("PAGER"));
        printf("LSCOLORS=%s\n", getenv("LSCOLORS"));
        printf("PATH=%s\n", getenv("PATH"));
        printf("LaunchInstanceID=%s\n", getenv("LaunchInstanceID"));
        printf("USER_ZDOTDIR=%s\n", getenv("USER_ZDOTDIR"));
        printf("PWD=%s\n", getenv("PWD"));
        printf("LANG=%s\n", getenv("LANG"));
        printf("ITERM_PROFILE=%s\n", getenv("ITERM_PROFILE"));
        printf("VSCODE_GIT_ASKPASS_EXTRA_ARGS=%s\n", getenv("VSCODE_GIT_ASKPASS_EXTRA_ARGS"));
        printf("XPC_FLAGS=%s\n", getenv("XPC_FLAGS"));
        printf("XPC_SERVICE_NAME=%s\n", getenv("XPC_SERVICE_NAME"));
        printf("VSCODE_INJECTION=%s\n", getenv("VSCODE_INJECTION"));
        printf("COLORFGBG=%s\n", getenv("COLORFGBG"));
        printf("HOME=%s\n", getenv("HOME"));
        printf("COLORFGBG=%s\n", getenv("COLORFGBG"));
        printf("SHLVL=%s\n", getenv("SHLVL"));
        printf("VSCODE_GIT_ASKPASS_MAIN=%s\n", getenv("VSCODE_GIT_ASKPASS_MAIN"));
        printf("LC_TERMINAL_VERSION=%s\n", getenv("LC_TERMINAL_VERSION"));
        printf("ITERM_SESSION_ID=%s\n", getenv("ITERM_SESSION_ID"));
        printf("LOGNAME=%s\n", getenv("LOGNAME"));
        printf("LESS=%s\n", getenv("LESS"));
        printf("VSCODE_GIT_IPC_HANDLE=%s\n", getenv("VSCODE_GIT_IPC_HANDLE"));
        printf("VSCODE_GIT_ASKPASS_NODE=%s\n", getenv("VSCODE_GIT_ASKPASS_NODE"));
        printf("GIT_ASKPASS=%s\n", getenv("GIT_ASKPASS"));
        printf("LC_TERMINAL=%s\n", getenv("LC_TERMINAL"));
        printf("SECURITYSESSIONID=%s\n", getenv("SECURITYSESSIONID"));
        printf("COLORTERM=%s\n", getenv("COLORTERM"));
        printf("_=%s\n", getenv("_"));
        while (env_vars)
        {
            printf("%s=%s\n", env_vars->env_name, env_vars->env_val);
            env_vars = env_vars->next;
        }
    }
}
