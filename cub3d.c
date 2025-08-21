/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:49:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/21 07:00:09 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsmap(char *ptr)
{
	int		len;
	int		i;
	char	*ex;

	len = ft_strlen(ptr) - 1;
	ex = ".cub";
	i = 3;
	if (len > 3)
	{
		while (i >= 0)
		{
			if (ptr[len--] != ex[i--])
				return (0);
		}
		return (1);
	}
	return (0);
}

t_list	*list_init(t_game *game)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->tail = 64;
	list->rows = game->map->height;
	list->cols = game->map->width;
	list->line = game->map->grid;
	list->w = 1280;
	list->h = 720;
	list->ww = list->tail * list->cols;
	list->wh = list->tail * list->rows;
	list->mlx = mlx_init(list->w, list->h, "cub3D", true);
	mlx_set_setting(MLX_MAXIMIZED, true);
	list->win = mlx_new_image(list->mlx, list->w, list->h);
	mlx_image_to_window(list->mlx, list->win, 0, 0);
	list->pi = M_PI;
	list->fov = 60 * (list->pi / 180);
	list->v = game->direction;
	list->mspeed = 7;
	list->rspeed = 2 * (list->pi / 180);
	list->vy = sin(list->v);
	list->vx = cos(list->v);
	list->px = game->map->player_x;
	list->py = game->map->player_y;
	list->game = game;
	return (list);
}

int	is_wall(t_list *list, double y, double x)
{
	double	j;
	double	i;

	if (x < 0 || x > list->ww || y < 0 || y > list->wh)
		return (1);
	j = floor(y / list->tail);
	i = floor(x / list->tail);
	if (list->line[(int) j][(int) i] == '1')
		return (1);
	return (0);
}

void	anime(void	*param)
{
	t_list			*list;

	list = param;
	(move0(list), move1(list), move11(list), move2(list), draw_p(list));
}

mlx_texture_t *load_png_texture(char *path)
{
    mlx_texture_t *texture;
    
    texture = mlx_load_png(path);
    if (!texture)
    {
        printf("Error: Failed to load texture: %s\n", path);
        return (NULL);
    }
    return (texture);
}

int load_all_textures(t_list *list)
{
    list->north_texture = load_png_texture("texter/no.png");
    if (!list->north_texture)
        return (0);
    list->south_texture = load_png_texture("texter/so.png");
    if (!list->south_texture)
        return (0);
    list->east_texture = load_png_texture("texter/ea.png");
    if (!list->east_texture)
        return (0);
    list->west_texture = load_png_texture("texter/we.png");
    if (!list->west_texture)
        return (0);
    list->tex_width = list->north_texture->width;
    list->tex_height = list->north_texture->height;
    return (1);
}

int	logic(t_list *list, t_game *game)
{
	list = list_init(game);
	list->f = 1;
	load_all_textures(list);
	draw_p0(list);
	mlx_key_hook(list->mlx, &move, list);
	mlx_loop_hook(list->mlx, &anime, list);
	mlx_loop(list->mlx);
	mlx_terminate(list->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_list	*list;
	t_game	*game;

	// atexit(f);
	list = NULL;
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
	logic(list, game);
	free_game(game);
	return (0);
}
