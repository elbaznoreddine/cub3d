#include "../cub3D.h"

int	init_game(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (0);
	return (1);
}
int	ft_check_map_extension(char *exten)
{
	size_t	len;

	len = ft_strlen(exten) - 4;
	if (!ft_strcmp(exten + len, ".cub"))
		return (1);
	return (0);
}

void	free_config(t_config *config)
{
	if (!config)
		return;
	if (config->path_north)
		free(config->path_north);
	if (config->path_south)
		free(config->path_south);
	if (config->path_west)
		free(config->path_west);
	if (config->path_east)
		free(config->path_east);
	if (config->floor)
		free(config->floor);
	if (config->ceil)
		free(config->ceil);
	free(config);
}

void	free_game(t_game *game)
{
	if (!game)
		return;
	free_config(game->config);
	free(game);
}