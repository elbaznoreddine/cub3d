#include "cub3D.h"

// void	f()
// {
// 	system("leaks cub3D");
// }

void put_big_pixel(void *mlx, void *win, int x, int y, int size, int color)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			mlx_pixel_put(mlx, win, x + i, y + j, color);
		}
	}
}

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
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, 1000,
			1000, "cub3D");
	if (!game->win)
		return (0);
	put_big_pixel(game->mlx, game->win, 100, 100, 50, game->floor);
	// mlx_pixel_put(game->mlx, game->win, 100, 100, game->floor);
	mlx_loop(game->mlx);
	//game logic
	
	// free_game(game);
	return (0);
}
