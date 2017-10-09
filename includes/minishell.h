#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>

typedef	struct		s_path
{
		struct 	s_path 	*next;
		char			*path;
}					t_path;

typedef	struct s_env
{
	char 	*name;
	char 	*value;
	struct 	s_env *next;
}					t_env;

typedef	struct 		s_msh
{
	t_env 	*env_lst ;
	t_path	*path;
	char	**env;
	char	**args;
	char	*pmt;
}					t_msh;

typedef	struct 		s_cmd
{
	char *line;
	struct s_cmd 	*next;
}					t_cmd;

t_env				*get_env(char **env);
void				disp_env(t_env *lst);
t_path				*get_path(t_env *e_lst);
void				built(t_msh *sh);
int					is_built(char *cmd);
t_path				*init_path(char *path);
t_env				*init_env(char *env_line);
void				free_tab(char **tab);
int					get_pmt(t_msh *sh);
int					size_env(t_env *env);
void				set_env(t_msh *sh);
void				maj_env(t_msh *sh);
void				unset_env(t_msh *sh);
char 				**create_env(void);
int					syntax_set(char **args);
t_cmd				*add_cmd(t_cmd *lst, char *line);
char				*find_env(t_env *env, char *name);
void				add_env(t_env *env, char *name, char *value);
int					mod_value(t_env *env, char *name, char *value);	
void				err_no(int n, char *s);
void				free_path(t_path *path);
char				**level_up(char **env, int lvl);
// fonction errno mytho obligatoire 
// check tous les chdir possible et message d erreur si pas ls droit ou path inconnu :
// unknow commande 
// profondeur env SHLVL;
// le split du path avc ":" // modif strsplit si string = a char c ;
// func del path pr no leaks