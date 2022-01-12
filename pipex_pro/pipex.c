#include "pipex.h"

static void	get_here_doc(t_info *info)
{
	int		len;
	char	*temp;

	info->total_document = ft_strdup("");
	len = ft_strlen(info->limiter);
	info->limiter[len] = '\n';
	len++;
	temp = get_next_line(0);
	while (ft_strncmp(temp, info->limiter, len))
	{
		info->total_document = ft_strjoin(info->total_document, temp);
		free(temp);
		temp = get_next_line(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	int			i;

	printf("\n");

	info.argv = argv;
	info.argc = argc;
	info.envp = envp;
	info.error_status = 0;
	info.is_here_doc = false;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
			exit(error_handler());
		info.is_here_doc = true;
		info.limiter = argv[2];
		get_here_doc(&info);
	}

	info.pid = (pid_t *)malloc(sizeof(pid_t) * (argc - 3 - info.is_here_doc));
	if (!info.pid)
		exit(1);  // 要修正
	info.pipefd = (int **)malloc(sizeof(int *) * (argc - 3));
	if (!info.pipefd)
		exit(1);

	i = 0;
	while (i < argc - 3)
	{
		info.pipefd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}

	info.error_status = start_process(info);
	// return (info.error_status);
	// printf("last%d\n", errno);
	// exit(0);
	printf("return : %d\n", info.error_status);
	exit (info.error_status);
}
