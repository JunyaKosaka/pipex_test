#include "pipex.h"

bool	is_valid_file(t_info info)
{
	// printf("5: %d\n", errno);
	if (access(info.argv[1], R_OK) == 0)
		return (true);
	return (false);
}

// static	int	path_index(t_info info)
// {
// 	int	index;

// 	index = 0;
// 	while (info.envp[index])
// 	{
// 		if (!ft_strncmp(info.envp[index], "PATH=", 5))
// 			return (index);
// 		index++;
// 	}
// 	return (-1);
// }

// bool	is_valid_cmds(t_info info)
// {
// 	char	**all_paths;
// 	char	*cmd_path;
// 	int		e_index;
// 	int		c_index;

// 	e_index = path_index(info);
// 	if (e_index == -1)
// 		return (false);
// 	all_paths = ft_split(&(info.envp[e_index][5]), ':');
// 	c_index = 0;
// 	while (all_paths[c_index])
// 	{
// 		cmd_path = ft_strjoin(all_paths[c_index], "/");
// 		cmd_path = ft_strjoin(cmd_path, info.argv[2]);
// 		if (!access(cmd_path, R_OK))
// 		{
// 			printf("%s\n", cmd_path);
// 			return (true);
// 		}
// 		c_index++;
// 	}
// 	return (false);
// }
