#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "minishell.h"
#include <errno.h>

void	ft_echo(char **params, char **env)
{	
	execve("/bin/echo", params, env);
}

// int		main(int argc, char **av, char **env)
// {
// 	DIR					*dir;
// 	struct dirent		*dirbuf;
// 	struct stat			statbuf;
	
// 	errno = 0;
// 	dir = opendir("/bin/");
// 	// while ((dirbuf = readdir(dir)))
// 	// {
// 	// 	printf("%s\n", dirbuf->d_name);
// 	// }
// 	execve("whereis", av, env);
// 	int test = stat(str, &statbuf);
// 	printf("%d\n", test);
// 	return (0);
// }

int	main(void)
{
	char	buf[10];
	read(1, buf, 10);
	return (0);
}
