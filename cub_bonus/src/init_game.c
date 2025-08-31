/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:09 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 19:39:26 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	init_player(t_map_mg *mg, t_game *game)
{
	char	dir;

	game->player.pos.x = (mg->player_pos[1] * TILE_SIZE) + (TILE_SIZE / 2);
	game->player.pos.y = (mg->player_pos[0] * TILE_SIZE) + (TILE_SIZE / 2);
	dir = mg->player_seen;
	if (dir == 'N')
		game->player.angle = 3 * M_PI / 2;
	else if (dir == 'S')
		game->player.angle = M_PI / 2;
	else if (dir == 'W')
		game->player.angle = M_PI;
	else
		game->player.angle = 0;
	game->player.go_right = 0;
	game->player.go_up = 0;
	game->player.rotate_right = 0;
	game->ceiling_color = mg->ceiling_color;
	game->floor_color = mg->floor_color;
}

static int	dup_map(char ***dst, char **map)
{
	char	**new_map;
	int		i;
	int		size;

	size = -1;
	while (map[++size])
		;
	new_map = malloc(sizeof(char *) * (size + 1));
	if (new_map == NULL)
		return (R_FAIL);
	i = -1;
	while (++i < size)
	{
		new_map[i] = ft_strdup(map[i]);
		if (new_map[i] == NULL)
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (R_FAIL);
		}
	}
	new_map[i] = NULL;
	*dst = new_map;
	return (R_SUCCESS);
}

static int	analyze_map(t_game *game, char *map_name)
{
	t_map_mg	*mg;

	mg = malloc(sizeof(t_map_mg));
	if (!mg)
		return (display_error_input_malloc(ERR_MALLOC_FAILED, NULL), R_FAIL);
	if (init_map_mg(mg))
		return (R_FAIL);
	if (apply_map_ope(map_name, mg))
		return (R_FAIL);
	if (dup_map(&game->map, mg->maps) == R_FAIL)
		return (free_map_mg(mg), R_FAIL);
	init_player(mg, game);
	if (load_textures(game, mg) == R_FAIL)
		return (free_map_mg(mg), free_map(game->map), R_FAIL);
	free_map_mg(mg);
	return (R_SUCCESS);
}

int	init_game(t_game *game, char *map_name)
{
	if (analyze_map(game, map_name) == R_FAIL)
		return (R_FAIL);
	game->ppd = (WIDTH / 2) / tan(deg_to_rad(FOV / 2));
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (clear_game(game), R_FAIL);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		return (clear_game(game), R_FAIL);
	game->player.is_over_gang = 10;
	return (R_SUCCESS);
}
