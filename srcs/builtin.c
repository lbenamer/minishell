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
}

void	maj_pwd(t_msh *sh)
{
	char *pwd;
	t_env *tmp;

	pwd = NULL;
	tmp = sh->env_lst;
	
	if((pwd = find_env(tmp, "PWD")))
		mod_value(tmp, "PWD", getcwd(NULL, 0));
	if(find_env(tmp, "OLDPWD"))
		mod_value(tmp, "OLDPWD", ft_strdup(pwd));
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
	char 	*tmp;

	// printf("cd start \n");
	if(sh->env_lst && !find_env(sh->env_lst, "PWD"))
	{
		printf("no PWD\n");
		tmp = getcwd(NULL, 0);
		add_env(sh->env_lst, "PWD", tmp);
		free(tmp);
		maj_pwd(sh);
	}
	if(sh->env_lst && !find_env(sh->env_lst, "OLDPWD"))
	{
		tmp = getcwd(NULL, 0);
		add_env(sh->env_lst, "OLDPWD", tmp);
		free(tmp);
		maj_pwd(sh);
	}
	if(!sh->env_lst)
	{
		free_tab(sh->env);
		sh->env = create_env();
		sh->env_lst = get_env(sh->env);
	}

	if(!sh->args[1] || !ft_strcmp(sh->args[1], "~"))
		tmp = find_env(sh->env_lst, "HOME");
	else if(!ft_strcmp(sh->args[1], "-"))
		tmp = get_old_pwd(sh->env_lst);
	else
		tmp = sh->args[1];
	if(tmp && !stat(tmp, &buf))
	{
		if(chdir(tmp) < 0)
			err_no(2, tmp);
		maj_pwd(sh);
	}
	else
		err_no(1, tmp);
	// printf("cd finish\n");
}

void	cmd_echo(char **args)
{
	int n;
	int i;

	i = 0;
	n = 0;
	if(!args[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if(args[1] && !ft_strcmp(args[1], "-n"))
	{
		++n;
		++i;
	}
	while(args[++i])
	{
		ft_putstr(args[i]);
		if(args[i + 1])
			write(1, " ", 1);
	}
	if(!n)
		write(1, "\n", 1);
}



void	built(t_msh *sh)
{
	if(!ft_strcmp(sh->args[0], "cd"))
		built_cd(sh);
	else if(!ft_strcmp(sh->args[0], "exit"))
		exit(1);
	else if(!ft_strcmp(sh->args[0], "env"))
		ft_printstab(sh->env);
	else if(!ft_strcmp(sh->args[0], "echo"))
		cmd_echo(sh->args);
	else if(!ft_strcmp(sh->args[0], "setenv"))
		set_env(sh);
	else if(!ft_strcmp(sh->args[0], "unsetenv"))
		unset_env(sh);
}