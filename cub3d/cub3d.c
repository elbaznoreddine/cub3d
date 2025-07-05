/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:49:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/05 16:45:52 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	list->mlx = mlx_init();
	list->win = 0;
	list->line = ft_split(*ptr);
	list->x = 2560;
	list->y = 1440;
	return (list);
}

void	ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	if (ptr && ptr[i])
		while (ptr[i])
			free(ptr[i++]);
	if (ptr)
	{
		free(ptr);
		ptr = 0;
	}
}

int	closew(t_list *list)
{
	list = 0;
	exit(0);
	return (0);
}

int	move(int key, t_list *list)
{
	if (key == 65307)
		exit(0);
	if (key == 119) // W
	{
		remove_p(list);
		list->py -= 16;
		draw_p(list);
	}
	if (key == 97) // A
	{
		remove_p(list);
		list->px -= 16;
		draw_p(list);
	}
	if (key == 115) // S
	{
		remove_p(list);
		list->py += 16;
		draw_p(list);
	}
	if (key == 100) // D
	{
		remove_p(list);
		list->px += 16;
		draw_p(list);
	}
	return (0);
}

int	logic(t_list *list, char **str)
{
	list = list_init(str);
	list->win = mlx_new_window(list->mlx, list->x, list->y, "so_long");
	if (!list->win)
		return (0);
	draw_map(list);
	mlx_hook(list->win, 17, 1, closew, list);
	mlx_hook(list->win, 2, 1, move, list);
	mlx_loop(list->mlx);
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
