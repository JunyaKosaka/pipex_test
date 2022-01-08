#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "./libft/libft.h"

// search "PATH=" index --->
int get_path_index(char *envp[])
{
  int envc = 0;

  // find char * pointing "PATH=..."
  while(*envp) {
    if (!strncmp(*envp, "PATH=", 5)) {
      return envc;
    }
    envc++;
    envp++;
  }
  return 0;
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	char	*path;
	char 	**all_path;
	// char	**envp;

	char buf[1024]; // PATH contains '762 words'

	strcpy(buf, envp[get_path_index(envp)]);

	// printf("path: %s\n", &buf[5]);
	all_path = ft_split(&buf[5], ':');
	i = 0;
	char *target;
	int	flag = 0;
	while (all_path[i])
	{
		if (access(argv[2], R_OK) == 0)
		{
			printf("%s ok\n", argv[2]);
			break ;
		}
		target = all_path[i];
		target = ft_strjoin(target, "/");
		target = ft_strjoin(target, argv[1]);
		if (access(target, R_OK) == 0)
		{
			printf("%s ok\n", target);
			flag = 1;
			break ;
		}
		printf("%s\n", all_path[i]);
		i++;
	}
	if (flag == 0)
		printf("ng\n");

	// i = 1;
	// while (i <= argc)
	// {
	// 	path = argv[i];
	// 	if (access(path, R_OK) == 0)
	// 	{
	// 		// access ok
	// 		printf("%s ok\n", path);
	// 	}
	// 	else
	// 	{
	// 		printf("%s ng\n", path);
	// 	}
	// 	i++;
	// }
}
