/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:22:59 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:23:01 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <sys/wait.h>
# define TYPE	(buf.st_mode & S_IFMT)

typedef struct		s_path
{
	struct s_path	*next;
	char			*path;
}					t_path;

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_msh
{
	t_env	*env_lst;
	t_path	*path;
	char	**env;
	char	**args;
	char	*pmt;
}					t_msh;

typedef struct		s_cmd
{
	char			*line;
	struct s_cmd	*next;
}					t_cmd;

t_env				*get_env(char **env);
void				disp_env(t_env *lst);
t_path				*get_path(t_env *e_lst);
void				built(t_msh *sh);
int					is_built(char *cmd);
t_path				*init_path(char *path);
t_env				*init_env(char *env_line);
void				free_tab(char **tab);
int					get_pmt(t_msh *sh);
int					size_env(t_env *env);
void				set_env(t_msh *sh);
void				maj_env(t_msh *sh);
void				unset_env(t_msh *sh);
char				**create_env(void);
int					syntax_set(char **args);
char				*find_env(t_env *env, char *name);
void				add_env(t_env *env, char *name, char *value);
int					mod_value(t_env *env, char *name, char *value);
void				err_no(int n, char *s);
void				free_path(t_path *path);
char				**level_up(char **env, int lvl);
int					check_arg(char *arg);
int					is_x(size_t n);
void				launch_env(t_msh *sh, char **env);
char				**dup_env(char	**env);
void				check_pwds(t_msh *sh);
char				*get_old_pwd(t_env *env);
void				maj_pwd(t_msh *sh);
char				**fork_env(t_msh sh);
void				del_elem(t_env *elem);
void				free_elem(t_env *elem);
void				print_pmt(char *pmt);
int					path_bin(char *line);
char				*add_slash(char *s1, char *s2);
#endif
