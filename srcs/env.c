#include "minishell.h"

void	free_elem(t_env *elem)
{
	free(elem->name);
	free(elem->value);
	free(elem);
}

void	del_elem(t_env *elem)
{
	t_env *tmp;

	tmp = elem->next;
	elem->next = elem->next->next;
	free_elem(tmp);
}

void	unset_env(t_msh *sh)
{
	t_env *tmp;
	t_env *env;

	env = sh->env_lst;
	if(env && !ft_strcmp(env->name, sh->args[1]))
	{
		tmp = env->next;
		free_elem(env);
		sh->env_lst = tmp;
		maj_env(sh);
		return ;
	}
	// tmp = env;
	while(env->next)
	{
		if(!ft_strcmp(env->next->name, sh->args[1]))
		{
			del_elem(env);
			maj_env(sh);
			return ;
		}
		env = env->next;
	}
	ft_printf("KEYS : %s : does not exist\n", sh->args[1]); // faire func errno mytho //
}

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