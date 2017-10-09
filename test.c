#include "includes/libft.h"
//#include "libft.h"
#include <stdio.h>

static size_t	ft_strnbsplit(const char *s, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
			--i;
		}
		i++;
	}
	return (j);
}

char			**ft_strsplit(const char *s, char c)
{
	size_t	i;
	size_t	start;
	char	**tab;
	size_t	n;

	n = 0;
	i = 0;
	tab = (char**)ft_memalloc(sizeof(char*) * ft_strnbsplit(s, c) + 1);
	if(!s)
		return (NULL);
	// printf("ok");
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			if (!(tab[n++] = ft_strsub(s, start, i - start)))
				return (NULL);
			--i;
		}
		i++;
	}
	tab[n] = 0;
	return (tab);
}

int main(int argc, char  **argv, char **env)
{
	char **tab;

	tab = ft_strsplit("::", ':');
	if(!tab[0])
		printf("NULL\n");
	else
		printf("tab\n");
	ft_printstab(tab);
	return 0;
}