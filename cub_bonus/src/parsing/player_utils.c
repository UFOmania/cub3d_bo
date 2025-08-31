/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:40:29 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 14:29:55 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_player_symbol(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	player_adjacent_to_space(char **maps, int row, int col)
{
	if (row <= 0 || col <= 0 || !maps[row + 1] || !maps[row][col + 1])
		return (1);
	if (maps[row][col + 1] == ' ' ||
		maps[row][col - 1] == ' ' ||
		maps[row + 1][col] == ' ' ||
		maps[row - 1][col] == ' ')
		return (1);
	return (0);
}

static int	find_players_in_map(t_map_mg *game_mg)
{
	int	row;
	int	col;

	if (!game_mg || !game_mg->maps)
		return (1);
	row = 0;
	game_mg->player_count = 0;
	while (game_mg->maps[row])
	{
		col = 0;
		while (game_mg->maps[row][col])
		{
			if (is_player_symbol(game_mg->maps[row][col]))
			{
				game_mg->player_seen = game_mg->maps[row][col];
				game_mg->player_pos[0] = row;
				game_mg->player_pos[1] = col;
				game_mg->maps[row][col] = '0';
				game_mg->player_count++;
			}
			col++;
		}
		row++;
	}
	return (0);
}

static int	validate_single_player(t_map_mg *game_mg)
{
	if (game_mg->player_count != 1)
	{
		if (game_mg->player_count == 0)
			print_error("Error: map has no player\n");
		else
			print_error("Error: map has too many players\n");
		return (1);
	}
	return (0);
}

int	check_player_in_map(t_map_mg *game_mg)
{
	if (!game_mg || !game_mg->maps)
		return (1);
	if (check_player_validity(game_mg->maps))
	{
		print_error("Error: player is adjacent to space or map edge\n");
		return (1);
	}
	if (find_players_in_map(game_mg))
	{
		print_error("Error: map \n");
		return (1);
	}
	if (validate_single_player(game_mg))
		return (1);
	return (0);
}
