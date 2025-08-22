/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:32 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/22 09:41:14 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_p0(t_list *list)
{
	int	x;
	int	y;

	y = 0;
	while (list->line[y])
	{
		x = 0;
		while (list->line[y][x])
		{
			if (list->line[y][x] == 'N' || list->line[y][x] == 'W' || list->line[y][x] == 'S' || list->line[y][x] == 'E')
			{
				list->py = y * list->tail + 32;
				list->px = x * list->tail + 32;
				draw_p(list);
				return ;
			}
			x++;
		}
		y++;
	}
}
