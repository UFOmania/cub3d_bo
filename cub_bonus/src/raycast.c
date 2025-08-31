/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:33 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 19:32:10 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	get_wall_height_and_margen(t_game *game, t_raycast_args *args)
{
	int	wall_hight;
	int	margen;

	wall_hight = (TILE_SIZE * game->ppd) / args->ray.len;
	margen = 0;
	if (wall_hight < HEIGHT)
		margen = HEIGHT - wall_hight;
	args->wall_h = wall_hight;
	args->margen = margen;
}

static void	get_texture_x(t_game *game, t_raycast_args *args)
{
	t_ray	ray;
	int		tex_x;
	int		side;

	tex_x = 0;
	side = args->ray.tex_hit_side;
	ray = args->ray;
	if (side == S || side == N)
		tex_x = (fmod(ray.hit_pos.x, TILE_SIZE)) * \
		game->texture[side]->width / TILE_SIZE;
	else if (side == W || side == E)
		tex_x = (fmod(ray.hit_pos.y, TILE_SIZE)) * \
		game->texture[side]->width / TILE_SIZE;
	args->tex_x = tex_x;
}

void	raycast(t_game *game)
{
	const double	fov = deg_to_rad(FOV);
	const double	step = fov / WIDTH;
	double			ray_angle;
	t_raycast_args	args;
	int				x;

	ray_angle = game->player.angle - (fov / 2);
	x = -1;
	while (++x < WIDTH)
	{
		args.ray = cast_ray(game, game->player.pos, ray_angle);
		args.ray.len = distance(game->player.pos, args.ray.hit_pos) * \
		cos(ray_angle - game->player.angle);
		args.x_on_screen = x;
		get_texture_x(game, &args);
		get_wall_height_and_margen(game, &args);
		do_render(game, &args);
		ray_angle = normilize_angle(ray_angle + step);
	}
}
