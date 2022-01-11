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
		if (!access(info->cmd_full_path, R_OK))
			return ;
		c_index++;
	}
	printf("no cmd\n");
	exit(1);
}
