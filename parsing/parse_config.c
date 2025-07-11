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
	if (type == 5) // floor
	{
		game->floor = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
	}
	else if (type == 6) // ceil
	{
		game->ceil = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
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
	return (free_split(arr), 0);
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

int	is_config(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C')
		return (1);
	return (0);
}

int	extract_direction(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!is_config(line[i]))
		return (0);
	if (line[i] != '\0')
	{
		if (!ft_strncmp(line + i, "NO", 2))
			return (1);
		if (!ft_strncmp(line + i, "SO", 2))
			return (2);
		if (!ft_strncmp(line + i, "WE", 2))
			return (3);
		if (!ft_strncmp(line + i, "EA", 2))
			return (4);
		if (!ft_strncmp(line + i, "F", 1))
			return (5);
		if (!ft_strncmp(line + i, "C", 1))
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
	while (line[i] && line[i] == ' ')
		i++;
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

int	ft_fill_config(t_game *game, int fd, char **first_map_line)
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
			*first_map_line = line;
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
		{
			free(direction);
			free(line);
			return (0);
		}
		free(line);
	}
	return (validate_config(game->config));
}
int	ft_fill_grid(t_game *game, char *map_lines, int map_height)
{
	int		i;
	int		j;
	int		k;
	char	*line;

	game->map->grid = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map->grid)
		return (0);
	game->map->height = map_height;
	game->map->width = 0;
	i = 0;
	k = 0;
	while (map_lines && map_lines[i] && k < map_height)
	{
		j = 0;
		while (map_lines[j + i] && map_lines[j + i] != '\n')
			j++;
		if (j > game->map->width)
			game->map->width = j;
		i += j;
		if (map_lines[i] == '\n')
			i++;
		k++;
	}
	i = 0;
	k = 0;
	while (map_lines && map_lines[i] && k < map_height)
	{
		j = 0;
		while (map_lines[j + i] && map_lines[j + i] != '\n')
			j++;
		line = ft_substr(map_lines, i, j);
		if (!line)
		{
			while (k > 0)
			{
				k--;
				free(game->map->grid[k]);
			}
			free(game->map->grid);
			return (0);
		}
		if (j < game->map->width)
		{
			int len = game->map->width - j;
			while (len-- > 0)
			{
				line = ft_strjoin(line, " ");
			}
		}
		game->map->grid[k] = line;
		i += j;
		if (map_lines[i] == '\n')
			i++;
		k++;
	}
	game->map->grid[k] = NULL;
	return (1);
}
int	ft_fill_map(t_game *game, int fd, char *first_map_line)
{
	char	*line;
	int		map_height = 1;
	char	*map_lines;

	if (!first_map_line)
	{
		return (0);
	}
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (free(first_map_line), 0);
	map_lines = ft_strdup(first_map_line);
	while ((line = get_next_line(fd)))
	{
		if (!line || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			return (free(map_lines), 0);
		}
		map_lines = ft_strjoin(map_lines, line);
		map_height++;
		free(line);
	}
	if (!ft_fill_grid(game, map_lines, map_height))
	{
		free(map_lines);
		return (0);
	}
	free(map_lines);
	free(first_map_line);
	return (1);
}
void	put_direction_player(t_game *game, char	direction)
{
	if (direction == 'N')
		game->direction = M_PI / 2;
	if (direction == 'S')
		game->direction = (3 * M_PI) / 2;
	if (direction == 'W')
		game->direction = M_PI;
	if (direction == 'E')
		game->direction = 0;
}
int	validate_map(t_game *game, t_map *map)
{
	int	i;
	int	j;
	int	len_player;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	i = 0;
	len_player = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] != '1' && map->grid[i][j] != '0' &&
				map->grid[i][j] != 'N' && map->grid[i][j] != 'S' &&
				map->grid[i][j] != 'E' && map->grid[i][j] != 'W' &&
				map->grid[i][j] != ' ')
			{
				return (0);
			}
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				put_direction_player(game, map->grid[i][j]);
				len_player++;
			}
			j++;
		}
		i++;
	}
	if (len_player != 1)
	{
		return (0);
	}
	return (1);
}
int	validate_dimensions(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	i = 0;

	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == 0 || i == map->height - 1)
			{
				if (map->grid[i][j] != '1' && map->grid[i][j] != ' ')
					return (0);
			}
			else if (j == 0 || j == map->width - 1)
			{
				if (map->grid[i][j] != '1' && map->grid[i][j] != ' ')
					return (0);
			}
			if (map->grid[i][j] == ' ' && (
                (j < map->width - 1 && map->grid[i][j + 1] == '0') ||
                (j > 0 && map->grid[i][j - 1] == '0') ||
                (i < map->height - 1 && map->grid[i + 1][j] == '0') ||
                (i > 0 && map->grid[i - 1][j] == '0')))
                return (0);
			j++;
		}
		i++;
	}
	return (1);
}
int	ft_parse_config(t_game *game, char *map_name)
{
	int	fd;
	char *first_map_line = NULL;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (free(game), 0);

	if (!ft_fill_config(game, fd, &first_map_line))
	{
		if (first_map_line)
			free(first_map_line);
		return (close(fd), 0);
	}
	if (!ft_fill_map(game, fd, first_map_line))
		return (close(fd), 0);
	if (!game->map || !game->config)
	{
		free(first_map_line);
		return (close(fd), 0);
	}
	if (!validate_map(game, game->map))
	{
		return (close(fd), 0);
	}
	if (!validate_dimensions(game->map))
	{
		return (close(fd), 0);
	}
	print_all_map(game);
	close(fd);
	return (1);
}