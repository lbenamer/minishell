/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:22:01 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/13 16:33:42 by lbenamer         ###   ########.fr       */
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
	if (is_x(buf.st_mode) && path_bin(sh.args[0]) && TYPE == S_IFREG)
	{
		++*f;
		pid = fork();
	}
	if (!pid)
	{
		if (!stat(sh.args[0], &buf))
		{
			if (execve(sh.args[0], sh.args, env_f))
				err_no(8, sh.args[0]);
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
			tmp = add_slash(sh.path->path, sh.args[0]);
			if (!stat(tmp, &buf) && check_arg(sh.args[0]) &&
				is_x(buf.st_mode) && TYPE == S_IFREG)
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
	int		ret;

	ret = 0;
	while (get_pmt(&sh))
	{
		sh.path = get_path(sh.env_lst);
		print_pmt(sh.pmt);
		ret = get_next_line(0, &buf);
		if (buf && buf[0] && ret)
			exec_msh(&sh, buf);
		if (ret > 0)
			ft_strdel(&buf);
		else
			exit(0);
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
