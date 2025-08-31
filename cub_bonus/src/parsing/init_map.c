/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:30:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 11:31:26 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	init_parsed_flags(t_map_mg *game_mg)
{
	int	i;

	if (!game_mg)
		return (1);
	i = 0;
	while (i < 6)
	{
		game_mg->parsed_flags[i] = -1;
		i++;
	}
	return (0);
}

int	init_floor_color(t_map_mg *game_mg)
{
	if (!game_mg)
		return (1);
	game_mg->floor_color = -1;
	game_mg->ceiling_color = -1;
	return (0);
}

int	init_map_mg(t_map_mg *game_mg)
{
	if (!game_mg)
		return (1);
	game_mg->maps = NULL;
	game_mg->north = NULL;
	game_mg->south = NULL;
	game_mg->west = NULL;
	game_mg->east = NULL;
	if (init_parsed_flags(game_mg))
		return (1);
	if (init_floor_color(game_mg))
		return (1);
	return (0);
}
