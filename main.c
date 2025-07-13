#include "cub3D.h"

// void	f()
// {
// 	system("leaks cub3D");
// }

int	main(int ac, char **av)
{
	t_game	*game;

	// atexit(f);
	game = NULL;
	if (ac != 2)
		return (write(2, "Error\n./cub3D /path/map.cub\n", 29), 1);
	if (!ft_check_map_extension(av[1]))
		return (write(2, "Error\nThe extention must be .cub\n", 34), 1);
	if (!init_game(&game))
		return (write(2, "Error\ncan't alocate memory\n", 28), 1);
	if (!parse_complete_map_file(game, av[1]))
	{
		free_game(game);
		return (write(2, "Error\nThe config or Map not valid\n", 35), 1);
	}
	free_game(game);
	return (0);
}
