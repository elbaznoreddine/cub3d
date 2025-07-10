#include "cub3D.h"

// void	f()
// {
// 	system("lsof -c cub3D");
// }

// void put_big_pixel(void *mlx, void *win, int x, int y, int size, int color)
// {
// 	int i, j;

// 	for (i = 0; i < size; i++)
// 	{
// 		for (j = 0; j < size; j++)
// 		{
// 			mlx_pixel_put(mlx, win, x + i, y + j, color);
// 		}
// 	}
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
	if (!ft_parse_config(game, av[1]))
	{
		free_game(game);
		return (write(2, "Error\nThe config or Map not valid\n", 35), 1);
	}
	// game->mlx = mlx_init();
	// if (!game->mlx)
	// 	return (0);
	// game->win = mlx_new_window(game->mlx, 1000,
	// 		1000, "cub3D");
	// if (!game->win)
	// 	return (0);
	// put_big_pixel(game->mlx, game->win, 100, 100, 50, game->floor);
	// // mlx_pixel_put(game->mlx, game->win, 100, 100, game->floor);
	// mlx_loop(game->mlx);
	// //game logic
	free_game(game);
	return (0);
}
