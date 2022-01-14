#include "pipex.h"

static	int	path_index(t_info info)
{
	int	index;

	index = 0;
	while (info.envp[index])
	{
		if (!ft_strncmp(info.envp[index], "PATH=", 5))
			return (index);
		index++;
	}
	return (-1);
}

void	convert_to_cmd_full_path(t_info *info, int i)
{
	char	**all_paths;
	int		e_index;
	int		c_index;

	i -= 2;
	if (!access(info->cmd[i][0], X_OK))
	{
		info->cmd_full_path[i] = ft_strdup(info->cmd[i][0]);
		return ;
	}
	e_index = path_index(*info);
	if (e_index == -1)
		exit(1);
	all_paths = ft_split(&(info->envp[e_index][5]), ':');
	if (!all_paths)
		exit(free_all_info(info, true));
	c_index = 0;
	while (all_paths[c_index])
	{
		// printf("cmd_full_path56:running: %d\n", i);
		char *temp;
		temp = ft_strjoin(all_paths[c_index], "/");
		info->cmd_full_path[i] = ft_strjoin(temp, info->cmd[i][0]);
		free(temp);
		if (!info->cmd_full_path[i])
		{
			free_2arr((void **)all_paths);
			exit(free_all_info(info, true));
		}
		if (!access(info->cmd_full_path[i], X_OK))
		{
			free_2arr((void **)all_paths);
			return ;
		}
		free(info->cmd_full_path[i]);
		info->cmd_full_path[i] = NULL;
		c_index++;
	}
	info->cmd_full_path[i] = ft_strdup("");
	free_2arr((void **)all_paths);
	write(2, "pipex: command not found: ", 26);
	ft_putendl_fd(info->cmd[i][0], 2);

	// perror(info->cmd[0]);
	// strerror(127);
	// info->error_status = 127;
	// exit(127); // 間違い　error statusは上書きして最後が残る
}
