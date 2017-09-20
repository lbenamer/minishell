#include "minishell.h"

void	disp_env(t_env *lst)
{
	while(lst)
	{
		printf("name = %s | value = %s\n", lst->name, lst->value);
		lst = lst->next;
	}
}

t_path 	*get_path(t_env *e_lst)
{
	char 	**tmp;
	int 	i;
	t_path 	*p_lst;
	t_path *ret;

	i = 0;
	while(e_lst)
	{
		if(!ft_strcmp(e_lst->name, "PATH"))
		{
			tmp = ft_strsplit(e_lst->value, ':');
			p_lst = init_path(tmp[0]);
			ret = p_lst;
			while(tmp[++i])
			{
				p_lst->next = init_path(tmp[i]);
				p_lst = p_lst->next;
			}
			free(tmp);
			return (ret);
		}
		e_lst = e_lst->next;
	}
	return (NULL);
}

t_env 	*get_env(char **env)
{
	t_env *lst_env;
	t_env *tmp;
	int i;
	
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