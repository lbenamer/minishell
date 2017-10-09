#include "minishell.h"

char	*cut_pmt(char *str)
{
	int i;
	int len;
	char *ret;
	if(!str)
		return (NULL);
	i = ft_strlen(str);
	len = i;
	if(!ft_strcmp(str, "/"))
		return (str);
	while(str[--i])
	{
		if(str[i] == '/')
		{
			ret	= ft_strsub(str, i + 1, len - i + 1);
			free(str);
			return (ret);
		}
	}
	return (str);
}

int	get_pmt(t_msh *sh)
{
	char *tmp;

	tmp = cut_pmt(getcwd(NULL, 0));
	if(tmp)
	{
		free(sh->pmt);
		sh->pmt = tmp;
	}
	return (1);
}

t_path 	*get_path(t_env *e_lst)
{
	char 	**tmp;
	int 	i;
	t_path 	*p_lst;
	t_path *ret;

	i = 0;
	p_lst = NULL;
	tmp = NULL;
	while(e_lst)
	{
		if(!ft_strcmp(e_lst->name, "PATH"))
		{
			tmp = ft_strsplit(e_lst->value, ':');
			if (tmp[0])
				p_lst = init_path(tmp[0]);
			ret = p_lst;
			while(tmp[0] && tmp[++i])
			{
				p_lst->next = init_path(tmp[i]);
				p_lst = p_lst->next;
			}
			free_tab(tmp);
			return (ret);
		}
		e_lst = e_lst->next;
	}
	return (NULL);
}

t_env 	*get_env(char **env)
{
	t_env	*lst_env;
	t_env	*tmp;
	int		i;
	
	lst_env = init_env(env[0]);
	tmp = lst_env;
	i = 0;
	while(env[++i])
	{
		lst_env->next = init_env(env[i]);
		lst_env = lst_env->next;
	}
	return (tmp);
}