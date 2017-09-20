#include "minishell.h"

void	disp_env(t_env *lst)
{
	while(lst)
	{
		printf("name = %s | value = %s\n", lst->name, lst->value);
		lst = lst->next;
	}
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