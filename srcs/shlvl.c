void level_up(t_env *env)
{
	char *tmp;
	int lvl;

	tmp = find_env(env, "SHLVL");
	lvl = ft_atoi(tmp);
	++lvl;
	tmp = ft_itoa(lvl);
	mod_value(env, "SHLVL", tmp);
}