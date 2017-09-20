#include "includes/libft.h"

int main(int argc, char  **argv, char **env)
{
	pid_t pid;
	// ft_putchar(9);
	// ft_putchar('\t');

	// ft_putchar(10);
	// ft_putchar('\n');

	// ft_putchar(11);
	// ft_putchar('\v');

	// ft_putchar(12);
	// ft_putchar('\f');

	// ft_putchar(13);
	// ft_putchar('\r');

		// ft_putchar(32);
	// ft_putchar(' ');
	pid = fork();
	chdir("/Users/iLak/42/");
	execve("/bin/ls", argv, env);
	// sleep(3);
	exit(1);
	return 0;
}