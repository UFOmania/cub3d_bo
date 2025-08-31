/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 12:58:59 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	is_wall(char **map, double x, double y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)(x / TILE_SIZE);
	tile_y = (int)(y / TILE_SIZE);
	if (tile_x < 0 || tile_y < 0)
		return (1);
	return (map[tile_y][tile_x] == '1');
}

static t_vec2	check_for_collision(char **map, \
t_vec2 player_pos, t_vec2 new_pos, int r)
{
	t_vec2	final_pos;

	final_pos = player_pos;
	if (!is_wall(map, new_pos.x + r, player_pos.y) && \
		!is_wall(map, new_pos.x - r, player_pos.y) && \
		!is_wall(map, new_pos.x, player_pos.y + r) && \
		!is_wall(map, new_pos.x, player_pos.y - r))
	{
		final_pos.x = new_pos.x;
	}
	if (!is_wall(map, player_pos.x, new_pos.y + r) && \
		!is_wall(map, player_pos.x, new_pos.y - r) && \
		!is_wall(map, player_pos.x + r, new_pos.y) && \
		!is_wall(map, player_pos.x - r, new_pos.y))
	{
		final_pos.y = new_pos.y;
	}
	return (final_pos);
}

void	apply_inputs(t_player *player, char **map)
{
	t_vec2	new_pos;
	t_vec2	pos;
	double	angle;
	int		up;
	int		right;

	pos = player->pos;
	angle = player->angle;
	right = player->go_right;
	up = player->go_up;
	new_pos.x = pos.x + (((cos(angle) * up) + \
						(cos(angle + (M_PI / 2)) * right)) * MOVE_SPEED);
	new_pos.y = pos.y + (((sin(angle) * up) + \
						(sin(angle + (M_PI / 2)) * right)) * MOVE_SPEED);
	player->pos = check_for_collision(map, pos, new_pos, PLAYER_RADIUS);
	if (player->rotate_right)
	{
		player->angle += ROT_SPEED * (double)player->rotate_right;
		if (player->angle >= M_PI * 2)
			player->angle = 0;
		if (player->angle < 0)
			player->angle = (M_PI * 2) - fabs(player->angle);
	}
}
