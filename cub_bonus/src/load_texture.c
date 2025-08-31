/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:17 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 12:49:18 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static mlx_image_t	*load_texture(t_game *game, char *src)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(src);
	if (tex == NULL)
		return (NULL);
	img = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	return (img);
}

int	load_textures(t_game *game, t_map_mg *mg)
{
	*(game->texture + S) = load_texture(game, mg->north);
	*(game->texture + N) = load_texture(game, mg->south);
	*(game->texture + E) = load_texture(game, mg->west);
	*(game->texture + W) = load_texture(game, mg->east);
	if (!*(game->texture + N) || !*(game->texture + S) || \
	!*(game->texture + W) || !*(game->texture + E))
	{
		mlx_delete_image(game->mlx, *(game->texture + S));
		mlx_delete_image(game->mlx, *(game->texture + N));
		mlx_delete_image(game->mlx, *(game->texture + W));
		mlx_delete_image(game->mlx, *(game->texture + E));
		return (mlx_strerror(mlx_errno), R_FAIL);
	}
	return (R_SUCCESS);
}
