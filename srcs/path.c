#include "minishell.h"

t_path 	*init_path(char *path)
{
	t_path *new;

	new = (t_path*)ft_memalloc(sizeof(t_env));
	new->path = ft_strdup(path);
	new->next = NULL;
	return (new);
}
t_env 	*init_env(char *env_line)
{
	char 	**tmp;
	t_env 	*new;
	
	new = (t_env*)ft_memalloc(sizeof(t_env));
	tmp = ft_strsplit(env_line, '=');
	new->name = ft_strdup(tmp[0]);
	new->value = ft_strdup(tmp[1]);
	new->next = NULL;
	free(tmp); // need to make a real func free for tab string // 
	return (new);
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