/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:22:01 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:22:02 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_args(t_msh sh, int *f, char **env_f)
{
	pid_t		pid;
	struct stat buf;

	pid = 1;
	if (stat(sh.args[0], &buf) || !check_arg(sh.args[0]))
		return (0);
	if (is_x(buf.st_mode) && (!ft_strncmp("./", sh.args[0], 2)
		|| sh.args[0][0] == '/'))
	{
		++*f;
		pid = fork();
	}
	if (!pid)
	{
		if (!stat(sh.args[0], &buf))
		{
			execve(sh.args[0], sh.args, env_f);
			exit(1);
		}
		else
			exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

void	launch(t_msh sh)
{
	pid_t			pid;
	char			*tmp;
	struct stat		buf;

	pid = fork();
	if (!pid)
	{
		while (sh.path)
		{
			sh.path->path = ft_strjoinf(sh.path->path, "/", 1);
			tmp = ft_strjoin(sh.path->path, sh.args[0]);
			if (!stat(tmp, &buf) && check_arg(sh.args[0]) && is_x(buf.st_mode))
			{
				execve(tmp, sh.args, sh.env);
				free(tmp);
				exit(1);
			}
			free(tmp);
			sh.path = sh.path->next;
		}
		err_no(3, sh.args[0]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_msh(t_msh *sh, char *buf)
{
	char	**env_f;
	int		f;

	f = 0;
	env_f = fork_env(*sh);
	sh->args = ft_strsplit_space(buf);
	free(buf);
	if (sh->args[0] && !is_built(sh->args[0]))
		exec_args(*sh, &f, env_f);
	if (!f && sh->args[0])
	{
		if (!is_built(sh->args[0]))
			launch(*sh);
		else
			built(sh);
	}
	free_tab(sh->args);
	free_tab(env_f);
}

void	minishell(t_msh sh)
{
	char	*buf;

	while (get_pmt(&sh))
	{
		sh.path = get_path(sh.env_lst);
		print_pmt(sh.pmt);
		get_next_line(0, &buf);
		if (buf && buf[0])
			exec_msh(&sh, buf);
		else
			free(buf);
		free_path(sh.path);
	}
}

int		main(int ac, char **av, char **env)
{
	t_msh	sh;

	ac = 1;
	av = NULL;
	sh.pmt = NULL;
	launch_env(&sh, env);
	minishell(sh);
	return (0);
}
