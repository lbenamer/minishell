/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:21:03 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:21:05 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_built(char *cmd)
{
	char	*built[6];
	int		i;

	i = -1;
	built[0] = "cd";
	built[1] = "setenv";
	built[2] = "unsetenv";
	built[3] = "exit";
	built[4] = "echo";
	built[5] = "env";
	while (++i < 6)
		if (!ft_strcmp(cmd, built[i]))
			return (1);
	return (0);
}

void	maj_env(t_msh *sh)
{
	int		i;
	char	*tmp;
	t_env	*env;

	env = sh->env_lst;
	i = 0;
	free_tab(sh->env);
	sh->env = (char**)ft_memalloc(sizeof(char*) * (size_env(env) + 1));
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		sh->env[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
}

void	built_cd(t_msh *sh)
{
	struct stat buf;
	char		*tmp;

	if (ft_size_tab(sh->args) > 2)
		return (err_no(5, "cd"));
	check_pwds(sh);
	if (!sh->args[1] || !ft_strcmp(sh->args[1], "~"))
		tmp = find_env(sh->env_lst, "HOME");
	else if (!ft_strcmp(sh->args[1], "-"))
		tmp = get_old_pwd(sh->env_lst);
	else
		tmp = sh->args[1];
	if (tmp && !stat(tmp, &buf))
	{
		if (chdir(tmp) < 0)
		{
			if ((buf.st_mode & S_IFMT) != S_IFDIR)
				err_no(6, tmp);
			else
				err_no(2, tmp);
		}
		maj_pwd(sh);
	}
	else
		err_no(1, tmp);
}

void	cmd_echo(char **args)
{
	int n;
	int i;

	i = 0;
	n = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		++n;
		++i;
	}
	while (args[++i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}

void	built(t_msh *sh)
{
	if (!ft_strcmp(sh->args[0], "cd"))
		built_cd(sh);
	else if (!ft_strcmp(sh->args[0], "exit"))
		exit(1);
	else if (!ft_strcmp(sh->args[0], "env"))
		ft_printstab(sh->env);
	else if (!ft_strcmp(sh->args[0], "echo"))
		cmd_echo(sh->args);
	else if (!ft_strcmp(sh->args[0], "setenv"))
		set_env(sh);
	else if (!ft_strcmp(sh->args[0], "unsetenv"))
		unset_env(sh);
}
