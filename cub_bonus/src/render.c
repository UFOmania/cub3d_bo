/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:37 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 19:32:17 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	render_ceiling_floor(mlx_image_t *img, \
t_raycast_args *a, int end, int color)
{
	while (a->y_on_screen < end)
	{
		mlx_put_pixel(img, a->x_on_screen, a->y_on_screen, color);
		a->y_on_screen++;
	}
}

static void	render_walls(t_game *game, t_raycast_args *a)
{
	int			tex_pos_on_wall;
	int			color;
	mlx_image_t	*texture;

	texture = game->texture[a->ray.tex_hit_side];
	tex_pos_on_wall = ((a->wall_h - HEIGHT) / 2);
	while (a->y_on_screen < HEIGHT - (a->margen / 2))
	{
		a->tex_y = ((a->y_on_screen + tex_pos_on_wall) * \
		texture->height / a->wall_h);
		color = get_pixel_color(texture, a->tex_x, a->tex_y);
		mlx_put_pixel(game->img, a->x_on_screen, a->y_on_screen, color);
		a->y_on_screen++;
	}
}

void	do_render(t_game *game, t_raycast_args *a)
{
	a->y_on_screen = 0;
	render_ceiling_floor(game->img, a, a->margen / 2, game->ceiling_color);
	render_walls(game, a);
	render_ceiling_floor(game->img, a, HEIGHT, game->floor_color);
}
