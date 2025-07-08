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
		return (write(2, "Usage: ./cub3D /path/map.cub\n", 30), 1);
	if (!ft_check_map_extension(av[1]))
		return (write(2, "Usage: The extention must be .cub\n", 35), 1);
	if (!init_game(&game))
		return (write(2, "Malloc: can't alocate memory\n", 30), 1);
	if (!ft_parse_config(game, av[1]))
	{
		free_game(game);
		return (write(2, "Parse: The config not valid\n", 28), 1);
	}
	
	//game logic
	
	// free_game(game);
	return (0);
}
