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
		// printf("tmp = %s\n", tmp);
		sh->env[i++] = ft_strjoin(tmp, env->value);
		// printf("env[i] = %s\n", sh->env[i - 1]);
		free(tmp);
		env = env->next;
	}
	// ft_printstab(sh->env);
}

void	maj_pwd(t_msh *sh)
{
	char *pwd;
	t_env *tmp;

	pwd = NULL;
	tmp = sh->env_lst;
	
	if((pwd = find_env(tmp, "PWD")))
	{
		// printf("find pwd = %s\n", pwd);
		mod_value(tmp, "PWD", getcwd(NULL, 0));
	}
	if(find_env(tmp, "OLDPWD"))
	{
		// printf("old = %s\n", old);
		mod_value(tmp, "OLDPWD", ft_strdup(pwd));
		//free(pwd);
	}	
	// disp_env(tmp);
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
		// printf("no env cd\n");
		free_tab(sh->env);
		sh->env = create_env();
		sh->env_lst = get_env(sh->env);
	}
	// if(!sh->args[1] || !ft_strcmp(sh->args[1], "~"))
	// {
	// 	tmp = find_env(sh->env_lst, "HOME");
	// 	if(tmp && !stat(tmp, &buf))
	// 	{
	// 		if(chdir(tmp) < 0)
	// 			err_no(2, tmp);
	// 		maj_pwd(sh);
	// 	}
	// 	else
	// 		err_no(1, tmp);
	// 	return ;
	// }
	// if(!ft_strcmp(sh->args[1], "-"))
	// {
	// 	tmp = get_old_pwd(sh->env_lst);
	// 	if(tmp && !stat(tmp, &buf))
	// 	{
	// 		if(chdir(tmp) < 0)
	// 			err_no(2, tmp);
	// 		maj_pwd(sh);
	// 	}
	// 	else
	// 		err_no(1, tmp);
	// 	return ;
	// }
	// else if(!stat(sh->args[1], &buf))
	// {
	// 	// printf("hear\n");
	// 	if(chdir(sh->args[1]) < 0)
	// 		err_no(2, sh->args[1])
	// 		// ft_printf("cd: permission denied: %s\n", sh->args[1]);
	// 	// printf("chdir ok\n");
	// 	maj_pwd(sh);
	// 	// printf("maj ok \n");
	// }
	// else
	// 	err_no(1, sh->args[1]);
		// ft_printf("cd: no such file or directory: %s\n", sh->args[1]);
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