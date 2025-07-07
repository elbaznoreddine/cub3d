#include "../cub3D.h"

int	put_into_struct(char *direction, int type, t_config *config)
{
	if (type == 1)
		config->path_north = direction;
	else if (type == 2)
		config->path_south = direction;
	else if (type == 3)
		config->path_west = direction;
	else if (type == 4)
		config->path_east = direction;
	else if (type == 5)
		config->floor = direction;
	else if (type == 6)
		config->ceil = direction;
	return (0);
}
int	extract_direction(char *line)
{
	size_t	i;

	i = 0;
	if (line[0] == '1')
		return (0);
	if (line[i] != '\0')
	{
		if (!ft_strncmp(line, "NO", 2))
			return (1);
		if (!ft_strncmp(line, "SO", 2))
			return (2);
		if (!ft_strncmp(line, "WE", 2))
			return (3);
		if (!ft_strncmp(line, "EA", 2))
			return (4);
		if (!ft_strncmp(line, "F", 1))
			return (5);
		if (!ft_strncmp(line, "C", 1))
			return (6);
	}
	return (-1);
}
char	*extract_path(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	if (line[i] == ' ')
		i++;
	if (line[i] && line[i] != ' ')
		return (ft_strdup(line + i));
	return (NULL);
}
int	ft_fill_config(t_game *game, int fd)
{
	char	*line;
	char	*direction;
	int		type;

	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (0);
	while ((line = get_next_line(fd)))
	{
		if (!line || line[0] == '\0')
			continue ;
		type = extract_direction(line);
		if (type == -1)
		{
			free(line);
			continue ;
		}
		if (type == 0)
			return (free(line), 1);
		if (type == 1)
			direction = extract_path(line);
		if (type == 2)
			direction = extract_path(line);
		if (type == 3)
			direction = extract_path(line);
		if (type == 4)
			direction = extract_path(line);
		if (type == 5)
			direction = extract_path(line);
		if (type == 6)
			direction = extract_path(line);
		put_into_struct(direction, type, game->config);
		free(line);
	}
	free(line);
	return (1);
}
int	ft_parse_config(t_game *game, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (free(game), 0);
	if (!ft_fill_config(game, fd))
		return (free(game), close(fd), 0);
	close(fd);
	if (game->config)
	{
		printf("[%s]\n[%s]\n[%s]\n[%s]\n[%s]\n[%s]\n",
			game->config->floor, game->config->ceil, game->config->path_north, game->config->path_south, game->config->path_east, game->config->path_west);
	}
	return (1);
}