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
	info.is_here_doc = false;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		info.is_here_doc = true;
		info.limiter = argv[2];  // エラー処理
		get_here_doc(&info);
	}
	else
	{
		if (!is_valid_file(info))
		{
			ft_putstr_fd("pipex: ", 2);
			perror(info.argv[1]);
			exit(1);
		}	
	}
	info.pipefd = (int **)malloc(sizeof(int *) * (argc - 3));
	if (!info.pipefd)
		exit(1);
	i = 0;
	while (i < argc - 3)
	{
		info.pipefd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	start_process(info);
	exit(0);
}
