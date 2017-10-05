#include "minishell.h"

int 	is_built(char *cmd)
{
	char *built[6] = {"cd", "setenv", "unsetenv", "exit", "echo", "env"};
	int 	i;

	i = -1;
	while(++i < 6)
		if(!ft_strcmp(cmd, built[i]))
			return (1);
	return (0);
}

void	maj_env(t_msh *sh)
{
	int i;
	char *tmp;
	t_env *env;

	env = sh->env_lst;
	i = 0;
	free_tab(sh->env);
	sh->env = (char**)ft_memalloc(sizeof(char*) * (size_env(env) + 1));
	while(env)
	{
		tmp = ft_strjoin(env->name, "=");
		sh->env[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	// ft_printstab(sh->env);
}

void	maj_pwd(t_msh *sh)
{
	char *pwd;
	t_env *tmp;

	tmp = sh->env_lst;
	while(tmp)
	{
		if(!ft_strcmp(tmp->name, "PWD"))
		{
			pwd = tmp->value;
			tmp->value = getcwd(NULL, 0);
			// free(buf);
		}
		if(!ft_strcmp(tmp->name, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			free(pwd);
		}
		tmp = tmp->next;
	}
	maj_env(sh);
}

char 	*get_old_pwd(t_env *env)
{
	while(env)
	{
		if(!ft_strcmp(env->name, "OLDPWD"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	built_cd(t_msh *sh)
{
	struct 	stat buf;

	if(!sh->env_lst)
	{
		printf("no env cd\n");
		sh->env = create_env();
		sh->env_lst = get_env(sh->env);
	}
	if(!sh->args[1])
		return ;
	if(!ft_strcmp(sh->args[1], "-"))
	{
		chdir(get_old_pwd(sh->env_lst));
		maj_pwd(sh);
	}
	else if(!stat(sh->args[1], &buf))
	{
		// ft_printf("hear\n");
		if(chdir(sh->args[1]) < 0)
			ft_printf("cd: permission denied: %s\n", sh->args[1]);
		maj_pwd(sh);
	}
	else
		ft_printf("cd: no such file or directory: %s\n", sh->args[1]);
}


void	built(t_msh *sh)
{
	// printf("built\n");

	if(!ft_strcmp(sh->args[0], "cd"))
		built_cd(sh);
	else if(!ft_strcmp(sh->args[0], "exit"))
		exit(1);
	else if(!ft_strcmp(sh->args[0], "env"))
		ft_printstab(sh->env);
	else if(!ft_strcmp(sh->args[0], "echo"))
		ft_printf("%s\n", sh->args[1]);
	else if(!ft_strcmp(sh->args[0], "setenv"))
		set_env(sh);
	else if(!ft_strcmp(sh->args[0], "unsetenv"))
		unset_env(sh); // faire la maj env char **//
}