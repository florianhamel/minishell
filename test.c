#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "includes/minishell.h"
#include <errno.h>

void	test_exit(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

int	main()
{
	int		fd;
	int		ret;
	char	*line;

	line = malloc(10);
	if ((fd = open("documents/.minishsdfell_history", O_RDONLY) < 0))
		test_exit();
	return (0);
}