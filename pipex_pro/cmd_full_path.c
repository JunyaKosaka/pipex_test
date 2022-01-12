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

void	convert_to_cmd_full_path(t_info *info)
{
	char	**all_paths;
	int		e_index;
	int		c_index;

	if (!access(info->cmd[0], R_OK))
	{
		info->cmd_full_path = info->cmd[0];
		return ;
	}
	e_index = path_index(*info);
	if (e_index == -1)
		exit(1);
	all_paths = ft_split(&(info->envp[e_index][5]), ':');
	c_index = 0;
	while (all_paths[c_index])
	{
		info->cmd_full_path = ft_strjoin(all_paths[c_index], "/");
		info->cmd_full_path = ft_strjoin(info->cmd_full_path, info->cmd[0]);
		if (!access(info->cmd_full_path, X_OK))
			return ;
		c_index++;
	}
	write(2, "pipex: command not found: ", 26);
	ft_putendl_fd(info->cmd[0], 2);
	// perror(info->cmd[0]);
	// strerror(127);
	info->error_status = 127;
	// exit(127); // 間違い　error statusは上書きして最後が残る
}
