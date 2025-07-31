/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:49:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/31 09:45:05 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

t_list	*list_init(char **ptr)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->tail = 64;
	list->rows = 11;
	list->cols = 17;
	list->line = ft_split(*ptr);
	list->ww = list->tail * list->cols;
	list->wh = list->tail * list->rows;
	list->mlx = mlx_init(list->ww, list->wh, "cub3D", true);
	mlx_set_setting(MLX_MAXIMIZED, true);
	list->win = mlx_new_image(list->mlx, list->ww, list->wh);
	mlx_image_to_window(list->mlx, list->win, 0, 0);
	list->pi = M_PI;
	list->fov = 60 * (list->pi / 180);
	list->v = 3 * list->pi / 2;
	list->mspeed = 20;
	list->rspeed = 20 * (list->pi / 180);
	list->vy = sin(list->v);
	list->vx = cos(list->v);
	list->f = 0.2;
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

int	logic(t_list *list, char **str)
{
	list = list_init(str);
	draw_map(list);
	mlx_key_hook(list->mlx, &move, list);
	mlx_loop(list->mlx);
	mlx_terminate(list->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_list	*list;
	char	*str;
	char	*ptr;
	int		fd;

	list = 0;
	if (ac != 2 || !parsmap(av[1]))
		return (0);
	str = 0;
	ptr = 0;
	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		return (0);
	ptr = get_next_line(fd);
	if (!ptr || ptr[0] == '\n')
		return (close(fd), free(ptr), get_next_line(-10), 0);
	while (ptr)
	{
		str = ft_strjoin(str, ptr);
		free(ptr);
		ptr = get_next_line(fd);
		if (!str || (ptr && str[ft_strlen(str) - 1] == '\n' && ptr[0] == '\n'))
			return (close(fd), free(str), free(ptr), get_next_line(-10), 0);
	}
	return (close(fd), logic(list, &str));
}
