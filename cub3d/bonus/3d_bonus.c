/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:58 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/23 10:44:59 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_3dwall0(t_list *list, int top, int down, int i)
{
	if (is_door(list))
	{
		while (top < down)
		{
			mlx_put_pixel(list->win, i, top, get_rgba(0, 0, 255, 255));
			top++;
		}
	}
	else
	{
		while (top < down)
		{
			mlx_put_pixel(list->win, i, top, get_rgba(255, 255, 255, 255));
			top++;
		}
	}
}

void	draw_3dwall(t_list *list, int top, int down, int i)
{
	int	z;

	z = 0;
	while (z < list->h / 2)
	{
		mlx_put_pixel(list->win, i, z, get_rgba(0, 0, 0, 255));
		z++;
	}
	while (z < list->h)
	{
		mlx_put_pixel(list->win, i, z, get_rgba(255, 0, 0, 255));
		z++;
	}
	draw_3dwall0(list, top, down, i);
}

void	draw_3d(t_list *list, double d, double v, int i)
{
	double	dp;
	double	wh;
	int		wsh;
	int		top;
	int		down;

	d *= cos(v - list->v);
	dp = (list->w / 2) / tan(list->fov / 2);
	wh = (list->tail / d) * dp;
	wsh = (int)wh;
	top = (list->h / 2) - (wsh / 2);
	if (top < 0)
		top = 0;
	down = (list->h / 2) + (wsh / 2);
	if (down > list->h)
		down = list->h;
	if (wsh <= 1)
	{
		top = list->h / 2;
		down = top + 1;
	}
	draw_3dwall(list, top, down, i);
}

void	draw_wall(t_list *list, double v, double i)
{
	double	x;
	double	y;
	double	d;

	x = 0;
	y = 0;
	list->hd = 1000000;
	list->vd = 1000000;
	if (list->hhit)
		list->hd = dis(list, list->hwally, list->hwallx);
	if (list->vhit)
		list->vd = dis(list, list->vwally, list->vwallx);
	if (list->hd < list->vd)
	{
		x = list->hwallx;
		y = list->hwally;
		d = list->hd;
	}
	else
	{
		x = list->vwallx;
		y = list->vwally;
		d = list->vd;
	}
	draw_3d(list, d, v, i);
}

void	draw_p(t_list *list)
{
	double	x;
	double	y;
	double	i;
	double	v;

	i = 0;
	v = list->v - (list->fov / 2);
	while (i < list->w)
	{
		reset_ang(list, &v);
		y = 0;
		x = 0;
		set_var(list);
		if (v > 0 && v < list->pi)
			list->up = 0;
		if ((v > list->pi / 2 && v < 3 * (list->pi / 2)))
			list->left = 1;
		(h_p(list, v, &y, &x), h_dda(list, y, x));
		(v_p(list, v, &y, &x), v_dda(list, y, x));
		draw_wall(list, v, i);
		v += (list->fov / list->w);
		i++;
	}
	draw_minimap(list);
}
