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
