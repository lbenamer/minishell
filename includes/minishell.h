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

// char	*lex_bin(char *cmd);
t_env 	*get_env(char **env);
void	disp_env(t_env *lst);
t_path 	*get_path(t_env *e_lst);
void	built(char **args, char **env);
int 	is_built(char *cmd);