/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:26:12 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/23 10:45:15 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_miniplayer(t_list	*list)
{
	double	i;
	double	j;
	double	x;

	j = 195;
	while (j <= 205)
	{
		i = 195;
		while (i++ <= 205)
			mlx_put_pixel(list->win, i * list->f, j * list->f, \
			get_rgba(255, 0, 0, 255));
		j++;
	}
	x = 0;
	j = 200;
	i = 200;
	while (x++ <= 50)
	{
		if (is_wall(list, list->py + j - 200, list->px + i - 200))
			break ;
		mlx_put_pixel(list->win, i * list->f, j * list->f, \
		get_rgba(255, 0, 0, 255));
		i += cos(list->v);
		j += sin(list->v);
	}
}

void	draw_minimap(t_list *list)
{
	double	y;
	double	x;
	double	i;
	double	j;

	i = 0;
	j = 0;
	y = list->py - 200;
	x = list->px - 200;
	while (j <= 400)
	{
		(1 && (i = 0, x = list->px - 200));
		while (i++ <= 400)
		{
			if (is_wall(list, y, x))
				mlx_put_pixel(list->win, i * list->f, j * list->f, \
				get_rgba(0, 0, 0, 255));
			else
				mlx_put_pixel(list->win, i * list->f, j * list->f, \
				get_rgba(128, 128, 128, 255));
			x++;
		}
		(1 && j++, y++);
	}
	draw_miniplayer(list);
}

int	is_door(t_list *list)
{
	if (list->hd < list->vd)
	{
		if (list->up)
			list->hwally -= 1;
		else
			list->hwally += 1;
		if (list->line[(int) floor(list->hwally / list->tail)][(int) \
		floor(list->hwallx / list->tail)] == 'D')
			return (1);
	}
	else
	{
		if (list->left)
			list->vwallx -= 1;
		else
			list->vwallx += 1;
		if (list->line[(int) floor(list->vwally / list->tail)][(int) \
		floor(list->vwallx / list->tail)] == 'D')
			return (1);
	}
	return (0);
}
