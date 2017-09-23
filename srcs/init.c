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
	free_tab(tmp);
	return (new);
}