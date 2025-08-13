/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:49:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/13 17:42:19 by yzoullik         ###   ########.fr       */
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
	list->rows = 20;
	list->cols = 18;
	list->line = ft_split(*ptr);
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
	list->v = 3 * list->pi / 2;
	list->mspeed = 7;
	list->rspeed = 5 * (list->pi / 180);
	list->vy = sin(list->v);
	list->vx = cos(list->v);
	return (list);
}

int	is_wall(t_list *list, double y, double x)
{
	double	j;
	double	i;

	if (x < 0 || x >= list->ww || y < 0 || y >= list->wh)
		return (1);
	j = floor(y / list->tail);
	i = floor(x / list->tail);
	if (list->line[(int) j][(int) i] == '1')
		return (1);
	return (0);
}

int	countlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				x;
	unsigned int	num;

	x = countlen(n);
	ptr = malloc((x + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[x] = '\0';
	num = n;
	if (n < 0)
	{
		ptr[0] = '-';
		num = -n;
	}
	while (x > 0)
	{
		if (x == 1 && n < 0)
			break ;
		ptr[x - 1] = (num % 10) + '0';
		num /= 10;
		x--;
	}
	return (ptr);
}

void	anime0(t_list *list, mlx_texture_t	*texture)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < (int)texture->height)
	{
		x = 0;
		while (x < (int)texture->width)
		{
			i = (y * texture->width + x) * 4;
			if (texture->pixels[i + 3] > 0)
				mlx_put_pixel(list->win, x, y, \
				((texture->pixels[i]) << 24) | ((texture->pixels[i + 1]) \
				<< 16) | ((texture->pixels[i + 2]) \
				<< 8) | texture->pixels[i + 3]);
			x++;
		}
		y++;
	}
}

void	anime(void	*param)
{
	t_list			*list;
	static int		j;
	char			*ptr;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	list = param;
	(move0(list), move1(list), move11(list), move2(list), draw_map1(list));
	j++;
	ptr = ft_strjoin(ft_strdup("bonus/png/"), ft_itoa(j));
	ptr = ft_strjoin(ptr, ".png");
	texture = mlx_load_png(ptr);
	img = mlx_texture_to_image(list->mlx, texture);
	anime0(list, texture);
	if (j == 40)
		j = 0;
	(mlx_delete_image(list->mlx, img), mlx_delete_texture(texture));
}

int	logic(t_list *list, char **str)
{
	list = list_init(str);
	list->f = 0.5;
	draw_map(list);
	mlx_key_hook(list->mlx, &move, list);
	mlx_loop_hook(list->mlx, &anime, list);
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
