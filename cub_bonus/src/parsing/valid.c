/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:41:08 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 14:30:22 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

bool	ispossible_characters(char c)
{
	return (c == ' ' || c == '1' || c == '0' || \
			c == '\n' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' );
}

bool	is_has_space_one_zero(char *line)
{
	int	i;

	if (!line || !*line)
		return (false);
	i = 0;
	while (line[i] != '\0')
	{
		if (!ispossible_characters(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	validate_game_mg(t_map_mg *game_mg)
{
	if (!game_mg->north || !game_mg->south || !game_mg->west || !game_mg->east)
		return (false);
	if (game_mg->floor_color == -1 || game_mg->ceiling_color == -1)
		return (false);
	return (true);
}

bool	is_valid_config_count(t_map_mg *game_mg)
{
	if (game_mg->parsed_flags[0] != 1)
		return (false);
	if (game_mg->parsed_flags[1] != 1)
		return (false);
	if (game_mg->parsed_flags[2] != 1)
		return (false);
	if (game_mg->parsed_flags[3] != 1)
		return (false);
	if (game_mg->parsed_flags[4] != 1)
		return (false);
	if (game_mg->parsed_flags[5] != 1)
		return (false);
	return (true);
}

int	check_player_validity(char **maps)
{
	int	row;
	int	col;

	if (!maps || !*maps)
		return (1);
	row = 0;
	while (maps[row])
	{
		col = 0;
		while (maps[row][col])
		{
			if (is_player_symbol(maps[row][col]) &&
				player_adjacent_to_space(maps, row, col))
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}
