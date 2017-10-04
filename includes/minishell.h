#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>



typedef struct 	s_path
{
		struct 	s_path 	*next;
		char			*path;
}				t_path;

typedef struct s_env
{
	char 	*name;
	char 	*value;
	struct 	s_env *next;
}				t_env;

typedef struct s_msh
{
	t_env 	*env_lst ;
	t_path	*path;
	char	**env;
	char	**args;
	char	*pmt;
}				t_msh;

// char	*lex_bin(char *cmd);
t_env 	*get_env(char **env);
void	disp_env(t_env *lst);
t_path 	*get_path(t_env *e_lst);
void	built(t_msh *sh);
int 	is_built(char *cmd);
t_path 	*init_path(char *path);
t_env 	*init_env(char *env_line);
void	free_tab(char **tab);
void	get_pmt(t_msh *sh);
int		size_env(t_env *env);
void	set_env(t_msh *sh);
void	maj_env(t_msh *sh);


// execute en premier instant la cmd enssuite check les bin//
// cree le pwd si pas de env
/// cree l env quand de env avc min pwd
// 