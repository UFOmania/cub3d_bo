/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:48:40 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 19:31:14 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static t_vec2	get_h_intercept(t_vec2 pos, double angle)
{
	t_vec2	h_intercept;

	h_intercept = (t_vec2){INFINITY, INFINITY};
	if (fabs(sin(angle)) > 0.0000001)
	{
		if (sin(angle) > 0)
			h_intercept.y = (floor(pos.y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		else
			h_intercept.y = floor(pos.y / TILE_SIZE) * TILE_SIZE - 0.00001;
		h_intercept.x = pos.x + ((h_intercept.y - pos.y) / tan(angle));
	}
	return (h_intercept);
}

static t_vec2	get_v_intercept(t_vec2 pos, double angle)
{
	t_vec2	v_intercept;

	v_intercept = (t_vec2){INFINITY, INFINITY};
	if (fabs(cos(angle)) > 0.0000001)
	{
		if (cos(angle) > 0)
			v_intercept.x = (floor(pos.x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		else
			v_intercept.x = floor(pos.x / TILE_SIZE) * TILE_SIZE - 0.00001;
		v_intercept.y = pos.y + ((v_intercept.x - pos.x) * tan(angle));
	}
	return (v_intercept);
}

static t_vec2	get_the_closest(t_ray *ray, t_vec2 pos, t_vec2 v, t_vec2 h)
{
	double	dv;
	double	dh;
	int		side;

	dv = INFINITY;
	dh = INFINITY;
	if (v.x != INFINITY)
		dv = (v.x - pos.x) / cos(ray->ray_angle);
	if (h.y != INFINITY)
		dh = (h.y - pos.y) / sin(ray->ray_angle);
	if (dv < dh)
		side = VERTICAL;
	else
		side = HORIZONTAL;
	if (side == HORIZONTAL && sin(ray->ray_angle) > 0)
		ray->tex_hit_side = N;
	else if (side == HORIZONTAL && sin(ray->ray_angle) < 0)
		ray->tex_hit_side = S;
	else if (side == VERTICAL && cos(ray->ray_angle) < 0)
		ray->tex_hit_side = E;
	else if (side == VERTICAL && cos(ray->ray_angle) > 0)
		ray->tex_hit_side = W;
	if (side == VERTICAL)
		return (v);
	return (h);
}

static int	is_wall(char **map, t_vec2 pos)
{
	int	x;
	int	y;

	x = pos.x / TILE_SIZE;
	y = pos.y / TILE_SIZE;
	if (map[y][x] == '1')
		return (1);
	return (0);
}

t_ray	cast_ray(t_game *game, t_vec2 start, double angle)
{
	t_vec2	pos;
	t_vec2	h_intercept;
	t_vec2	v_intercept;
	t_vec2	closest;
	t_ray	ray;

	ray.ray_angle = angle;
	pos = start;
	while (1)
	{
		h_intercept = get_h_intercept(pos, angle);
		v_intercept = get_v_intercept(pos, angle);
		closest = get_the_closest(&ray, pos, v_intercept, h_intercept);
		if (is_wall(game->map, closest))
			break ;
		else
			pos = closest;
	}
	ray.hit_pos = closest;
	return (ray);
}
