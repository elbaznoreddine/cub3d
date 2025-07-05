/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:32 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/05 16:27:57 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_1(int x, int y, t_list *list)
{
	int	ey;
	int	ex;

	ey = y + 64;
	ex = x + 64;
	if (ey == 0)
		ey = 64;
	if (ex == 0)
		ex = 64;
	while (y + 1 < ey)
	{
		if (ex == 64)
			x = 0;
		else
			x = ex - 64;
		while (x + 1 < ex)
		{
			mlx_pixel_put(list->mlx, list->win, x, y, 16777215);
			x++;
		}
		y++;
	}
}

void	draw_0(int x, int y, t_list *list)
{
	int	ey;
	int	ex;

	ey = y + 64;
	ex = x + 64;
	if (ey == 0)
		ey = 64;
	if (ex == 0)
		ex = 64;
	while (y + 1 < ey)
	{
		if (ex == 64)
			x = 0;
		else
			x = ex - 64;
		while (x + 1 < ex)
		{
			mlx_pixel_put(list->mlx, list->win, x, y, 8421504);
			x++;
		}
		y++;
	}
}

void	draw_p(t_list *list)
{
	int	y;
	int	x;
	int	ey;
	int	ex;

	y = list->py;
	x = list->px;
	y += (64 / 2) - 16;
	x += (64 / 2) - 1;
	ey = y + 32;
	ex = x + 2;
	if (ey == 0)
		ey = 64;
	if (ex == 0)
		ex = 64;
	while (y < ey)
	{
		if (ex == 64)
			x = 0;
		else
			x = ex - 2;
		while (x < ex)
		{
			mlx_pixel_put(list->mlx, list->win, x, y, 16711680);
			x++;
		}
		y++;
	}
}

void	remove_p(t_list *list)
{
	int	y;
	int	x;
	int	ey;
	int	ex;

	y = list->py;
	x = list->px;
	y += (64 / 2) - 16;
	x += (64 / 2) - 1;
	ey = y + 32;
	ex = x + 2;
	if (ey == 0)
		ey = 64;
	if (ex == 0)
		ex = 64;
	while (y < ey)
	{
		if (ex == 64)
			x = 0;
		else
			x = ex - 2;
		while (x < ex)
		{
			mlx_pixel_put(list->mlx, list->win, x, y, 8421504);
			x++;
		}
		y++;
	}
}

void	draw_map(t_list *list)
{
	int	x;
	int	y;

	y = 0;
	while (list->line[y])
	{
		x = 0;
		while (list->line[y][x])
		{
			if (list->line[y][x] == '1')
				draw_1(x * 64, y * 64, list);
			if (list->line[y][x] == '0' || list->line[y][x] == 'P')
				draw_0(x * 64, y * 64, list);
			x++;
		}
		y++;
	}
	y = 0;
	while (list->line[y])
	{
		x = 0;
		while (list->line[y][x])
		{
			if (list->line[y][x] == 'P')
			{
				list->py = y * 64;
				list->px = x * 64;
				draw_p(list);
				return ;
			}
			x++;
		}
		y++;
	}
}
