#include "minishell.h"


void	add_env(t_env *env, char *name, char *value)
{
	t_env *new;

	new = (t_env*)ft_memalloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	while(env->next)
		env = env->next;
	env->next = new;
}

void	set_env(t_msh *sh)
{
	t_env *tmp;

	tmp = sh->env_lst;
	if(!sh->args[1])
	{
		ft_printstab(sh->env);
		return ;
	}
	while(tmp)
	{
		if(!ft_strcmp(tmp->name, sh->args[1]))
		{
			printf("hear\n");
			free(tmp->value);
			if(sh->args[2])
				tmp->value = ft_strdup(sh->args[2]);
			else
				tmp->value = ft_strnew(0);
			maj_env(sh);
			return ;
		}
		tmp = tmp->next;
	}
	add_env(sh->env_lst, sh->args[1], sh->args[2]);
	maj_env(sh);
}