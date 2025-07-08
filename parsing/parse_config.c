#include "../cub3D.h"

int are_valid_to_store(char *direction)
{
	int	fd;

	fd = open(direction, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	validate_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) == -1)
			return (1);
		i++;
	}
	if (i > 3)
		return (1);
	return (0);
}

void	ft_fill_floor_ceil(t_game *game, char **rgb, int type)
{
	unsigned int	ceil;
	unsigned int	floor;

	if (type == 5) // floor
	{
		ft_memset(&floor, 0, 4);
		ft_memset(&floor + 1, ft_atoi(rgb[0]), 3);
		ft_memset(&floor + 1, ft_atoi(rgb[1]), 2);
		ft_memset(&floor + 1, ft_atoi(rgb[2]), 1);
		game->floor = floor;
	}
	else if (type == 6)
	{
		ft_memset(&ceil, 0, 4);
		ft_memset(&ceil + 1, ft_atoi(rgb[0]), 3);
		ft_memset(&ceil + 1, ft_atoi(rgb[1]), 2);
		ft_memset(&ceil + 1, ft_atoi(rgb[2]), 1);
		game->ceil = ceil;
	}
}

int are_valid_to_store_f_c(t_game *game, char *direction, int type)
{
	int	i;
	char	**arr;

	i = 0;
	arr = NULL;
	while (direction[i])
	{
		if (direction[i] && direction[i] == ',' && direction[i + 1] == ',')
			return (1);
		i++;
	}
	arr = ft_split(direction, ',');
	if (!arr)
		return (1);
	if (validate_rgb(arr))
		return (free_split(arr), 1);
	ft_fill_floor_ceil(game, arr, type);
	return (0);
}
int	put_into_struct(char *direction, int type, t_config *config, t_game *game)
{
	if (type == 1)
	{
		if (are_valid_to_store(direction))
			return (0);
		config->path_north = direction;
		return (1);
	}
	else if (type == 2)
	{
		if (are_valid_to_store(direction))
			return (0);
		config->path_south = direction;
		return (1);
	}
	else if (type == 3)
	{
		if (are_valid_to_store(direction))
			return (0);
		config->path_west = direction;
		return (1);
	}
	else if (type == 4)
	{
		if (are_valid_to_store(direction))
			return (0);
		config->path_east = direction;
		return (1);
	}
	else if (type == 5)
	{
		if (are_valid_to_store_f_c(game, direction, type))
			return (0);
		config->floor = direction;
		return (1);
	}
	else if (type == 6)
	{
		if (are_valid_to_store_f_c(game, direction, type))
			return (0);
		config->ceil = direction;
		return (1);
	}
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
int	init_config(t_config *config)
{
	config->path_north = NULL;
	config->path_south = NULL;
	config->path_west = NULL;
	config->path_east = NULL;
	config->floor = NULL;
	config->ceil = NULL;
	return (1);
}
int	validate_config(t_config *config)
{
	if (!config->path_north || !config->path_south || 
		!config->path_west || !config->path_east ||
		!config->floor || !config->ceil)
		return (0);
	return (1);
}
char	*extract_path(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*path;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	end = i;
	while (end > start && line[end - 1] == ' ')
		end--;
	if (start >= end)
		return (NULL);
	path = malloc(end - start + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, line + start, (end - start) + 1);
	path[end - start] = '\0';
	return (path);
}

int	is_already_set(t_config *config, int type)
{
	if (type == 1 && config->path_north)
		return (1);
	if (type == 2 && config->path_south)
		return (1);
	if (type == 3 && config->path_west)
		return (1);
	if (type == 4 && config->path_east)
		return (1);
	if (type == 5 && config->floor)
		return (1);
	if (type == 6 && config->ceil)
		return (1);
	return (0);
}

int	ft_fill_config(t_game *game, int fd)
{
	char	*line;
	char	*direction;
	int		type;

	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (0);
	init_config(game->config);
	
	while ((line = get_next_line(fd)))
	{
		if (!line || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue;
		}
		type = extract_direction(line);
		if (type == -1)
		{
			free(line);
			continue;
		}
		if (type == 0)
		{
			free(line);
			return (validate_config(game->config));
		}
		if (is_already_set(game->config, type))
		{
			free(line);
			return (0);
		}
		direction = extract_path(line);
		if (!direction)
		{
			free(line);
			return (0);
		}
		if (!put_into_struct(direction, type, game->config, game))
			return (free(line), 0);
		free(line);
	}
	return (validate_config(game->config));
}

int	ft_parse_config(t_game *game, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (free(game), 0);
	if (!ft_fill_config(game, fd))
		return (close(fd), 0);
	close(fd);
	if (game->config)
	{
		printf("[%s]\n[%s]\n[%s]\n[%s]\n[%s]\n[%s]\n",
			game->config->floor, game->config->ceil, game->config->path_north, game->config->path_south, game->config->path_east, game->config->path_west);
	}
	printf("[%u] [%u]\n", game->floor, game->ceil);
	return (1);
}