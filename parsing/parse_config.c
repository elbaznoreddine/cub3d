#include "../cub3D.h"

int	can_open_texture_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	are_rgb_values_valid(char **rgb_array)
{
	int	i;

	i = 0;
	while (rgb_array[i])
	{
		if (ft_atoi(rgb_array[i]) == -1)
			return (1);
		i++;
	}
	if (i > 3 || i < 3)
		return (1);
	return (0);
}

void	store_color_in_game(t_game *game, char **rgb_array, int color_type)
{
	if (color_type == 5)
	{
		game->floor = (ft_atoi(rgb_array[0]) << 16) | 
			(ft_atoi(rgb_array[1]) << 8) | ft_atoi(rgb_array[2]);
	}
	else if (color_type == 6)
	{
		game->ceil = (ft_atoi(rgb_array[0]) << 16) | 
			(ft_atoi(rgb_array[1]) << 8) | ft_atoi(rgb_array[2]);
	}
}

int	has_consecutive_commas(char *color_string)
{
	int	i;

	i = 0;
	while (color_string[i])
	{
		if (color_string[i] && color_string[i] == ',' && 
			color_string[i + 1] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	validate_and_store_color(t_game *game, char *color_string, int color_type)
{
	char	**rgb_array;

	if (has_consecutive_commas(color_string))
		return (1);
	rgb_array = ft_split(color_string, ',');
	if (!rgb_array)
		return (1);
	if (are_rgb_values_valid(rgb_array))
		return (free_split(rgb_array), 1);
	store_color_in_game(game, rgb_array, color_type);
	return (free_split(rgb_array), 0);
}

int	store_north_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_north = texture_path;
	return (1);
}

int	store_south_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_south = texture_path;
	return (1);
}

int	store_west_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_west = texture_path;
	return (1);
}

int	store_east_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_east = texture_path;
	return (1);
}

int	store_floor_color(t_game *game, char *color_string, t_config *config)
{
	if (validate_and_store_color(game, color_string, 5))
		return (0);
	config->floor = color_string;
	return (1);
}

int	store_ceiling_color(t_game *game, char *color_string, t_config *config)
{
	if (validate_and_store_color(game, color_string, 6))
		return (0);
	config->ceil = color_string;
	return (1);
}

int	save_config_element(char *element_value, int element_type, 
	t_config *config, t_game *game)
{
	if (element_type == 1)
		return (store_north_texture(element_value, config));
	else if (element_type == 2)
		return (store_south_texture(element_value, config));
	else if (element_type == 3)
		return (store_west_texture(element_value, config));
	else if (element_type == 4)
		return (store_east_texture(element_value, config));
	else if (element_type == 5)
		return (store_floor_color(game, element_value, config));
	else if (element_type == 6)
		return (store_ceiling_color(game, element_value, config));
	return (0);
}

int	is_valid_config_character(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C')
		return (1);
	return (0);
}

int	identify_config_type(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!is_valid_config_character(line[i]))
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

int	setup_empty_config(t_config *config)
{
	config->path_north = NULL;
	config->path_south = NULL;
	config->path_west = NULL;
	config->path_east = NULL;
	config->floor = NULL;
	config->ceil = NULL;
	return (1);
}

int	check_config_completeness(t_config *config)
{
	if (!config->path_north || !config->path_south
	|| !config->path_west || !config->path_east
	|| !config->floor || !config->ceil)
		return (0);
	return (1);
}

char	*extract_file_path(char *line)
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

int	config_element_already_exists(t_config *config, int element_type)
{
	if (element_type == 1 && config->path_north)
		return (1);
	if (element_type == 2 && config->path_south)
		return (1);
	if (element_type == 3 && config->path_west)
		return (1);
	if (element_type == 4 && config->path_east)
		return (1);
	if (element_type == 5 && config->floor)
		return (1);
	if (element_type == 6 && config->ceil)
		return (1);
	return (0);
}

int	process_config_line(t_game *game, char *line, int *element_type, 
	char **first_map_line)
{
	char	*element_value;

	*element_type = identify_config_type(line);
	if (*element_type == -1)
		return (2);
	if (*element_type == 0)
	{
		*first_map_line = line;
		return (1);
	}
	if (config_element_already_exists(game->config, *element_type))
		return (0);
	element_value = extract_file_path(line);
	if (!element_value)
		return (0);
	if (!save_config_element(element_value, *element_type, game->config, game))
	{
		free(element_value);
		return (0);
	}
	return (2);
}

int	parse_configuration_section(t_game *game, int fd, char **first_map_line)
{
	char	*line;
	int		element_type;
	int		process_result;

	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (0);
	setup_empty_config(game->config);
	line = get_next_line(fd);
	while (line)
	{
		if (!line || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		process_result = process_config_line(game, line, &element_type, 
			first_map_line);
		if (process_result == 0)
			return (free(line), 0);
		if (process_result == 1)
			return (check_config_completeness(game->config));
		free(line);
		line = get_next_line(fd);
	}
	return (check_config_completeness(game->config));
}

int	calculate_map_dimensions(t_game *game, char *map_content, int map_height)
{
	int	i;
	int	j;
	int	k;

	game->map->height = map_height;
	game->map->width = 0;
	i = 0;
	k = 0;
	while (map_content && map_content[i] && k < map_height)
	{
		j = 0;
		while (map_content[j + i] && map_content[j + i] != '\n')
			j++;
		if (j > game->map->width)
			game->map->width = j;
		i += j;
		if (map_content[i] == '\n')
			i++;
		k++;
	}
	return (1);
}

char	*pad_map_line_with_spaces(char *line, int current_length, int max_width)
{
	int	spaces_needed;

	if (current_length < max_width)
	{
		spaces_needed = max_width - current_length;
		while (spaces_needed-- > 0)
			line = ft_strjoin(line, " ");
	}
	return (line);
}

int	extract_and_store_map_line(t_game *game, char *map_content, int *position, 
	int line_index)
{
	int		j;
	char	*line;

	j = 0;
	while (map_content[j + *position] && map_content[j + *position] != '\n')
		j++;
	line = ft_substr(map_content, *position, j);
	if (!line)
		return (0);
	if (j < game->map->width)
		line = pad_map_line_with_spaces(line, j, game->map->width);
	game->map->grid[line_index] = line;
	*position += j;
	if (map_content[*position] == '\n')
		(*position)++;
	return (1);
}

int	fill_map_grid_with_content(t_game *game, char *map_content, int map_height)
{
	int	position;
	int	line_index;

	game->map->grid = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map->grid)
		return (0);
	calculate_map_dimensions(game, map_content, map_height);
	position = 0;
	line_index = 0;
	while (map_content && map_content[position] && line_index < map_height)
	{
		if (!extract_and_store_map_line(game, map_content, &position, 
			line_index))
		{
			while (line_index > 0)
			{
				line_index--;
				free(game->map->grid[line_index]);
			}
			free(game->map->grid);
			return (0);
		}
		line_index++;
	}
	game->map->grid[line_index] = NULL;
	return (1);
}

int	read_entire_map_content(t_game *game, int fd, char *first_map_line)
{
	char	*line;
	int		map_height;
	char	*map_content;

	map_height = 1;
	map_content = ft_strdup(first_map_line);
	line = get_next_line(fd);
	while (line)
	{
		if (!line || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			return (free(map_content), 0);
		}
		map_content = ft_strjoin(map_content, line);
		map_height++;
		free(line);
		line = get_next_line(fd);
	}
	if (!fill_map_grid_with_content(game, map_content, map_height))
		return (free(map_content), 0);
	free(map_content);
	return (1);
}

int	parse_map_section(t_game *game, int fd, char *first_map_line)
{
	if (!first_map_line)
		return (0);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (free(first_map_line), 0);
	game->map->grid = NULL;
	game->map->height = 0;
	game->map->width = 0;
	game->map->player_x = 0;
	game->map->player_y = 0;
	if (!read_entire_map_content(game, fd, first_map_line))
		return (free(first_map_line), 0);
	free(first_map_line);
	return (1);
}

void	set_player_facing_direction(t_game *game, char direction_char)
{
	if (direction_char == 'N')
		game->direction = M_PI / 2;
	if (direction_char == 'S')
		game->direction = (3 * M_PI) / 2;
	if (direction_char == 'W')
		game->direction = M_PI;
	if (direction_char == 'E')
		game->direction = 0;
}

int	is_valid_map_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && 
		c != 'E' && c != 'W' && c != ' ')
		return (0);
	return (1);
}

int	is_player_character(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	count_players_and_validate_chars(t_game *game, t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_map_character(map->grid[i][j]))
				return (-1);
			if (is_player_character(map->grid[i][j]))
			{
				set_player_facing_direction(game, map->grid[i][j]);
				game->map->player_x = j;
				game->map->player_y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count);
}

int	validate_map_content(t_game *game, t_map *map)
{
	int	player_count;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	player_count = count_players_and_validate_chars(game, map);
	if (player_count != 1)
		return (0);
	return (1);
}

int	is_border_position(int i, int j, t_map *map)
{
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		return (1);
	return (0);
}

int	has_invalid_border_character(char c)
{
	if (c != '1' && c != ' ')
		return (1);
	return (0);
}

int	space_touches_empty_cell(t_map *map, int i, int j)
{
	if (map->grid[i][j] == ' ')
	{
		if ((j < map->width - 1 && map->grid[i][j + 1] == '0') ||
			(j > 0 && map->grid[i][j - 1] == '0') ||
			(i < map->height - 1 && map->grid[i + 1][j] == '0') ||
			(i > 0 && map->grid[i - 1][j] == '0'))
			return (1);
	}
	return (0);
}

int	validate_map_boundaries(t_map *map)
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
			if (is_border_position(i, j, map))
			{
				if (has_invalid_border_character(map->grid[i][j]))
					return (0);
			}
			if (space_touches_empty_cell(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_complete_map_file(t_game *game, char *map_filename)
{
	int		fd;
	char	*first_map_line;

	first_map_line = NULL;
	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!parse_configuration_section(game, fd, &first_map_line))
	{
		if (first_map_line)
			free(first_map_line);
		return (close(fd), 0);
	}
	if (!parse_map_section(game, fd, first_map_line))
		return (close(fd), 0);
	if (!game->map || !game->config)
		return (close(fd), 0);
	if (!validate_map_content(game, game->map))
		return (close(fd), 0);
	if (!validate_map_boundaries(game->map))
		return (close(fd), 0);
	print_all_map(game);
	close(fd);
	return (1);
}
