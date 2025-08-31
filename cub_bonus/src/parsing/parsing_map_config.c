/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:31:46 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 14:29:25 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	check_config_position(int index)
{
	if (index != 0)
	{
		print_error("❌ Config found under map at line \n");
		return (1);
	}
	return (0);
}

int	parse_no_so(t_map_mg *game_mg, char *line, int index)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !check_config_position(index))
	{
		if (game_mg->parsed_flags[0] != -1)
			return (display_error_direction(ERR_DUPLICATE_NO));
		game_mg->north = is_valid_texture(line, "NO");
		if (!game_mg->north)
			return (1);
		game_mg->parsed_flags[0] = 1;
		return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !check_config_position(index))
	{
		if (game_mg->parsed_flags[1] != -1)
			return (display_error_direction(ERR_DUPLICATE_SO));
		game_mg->south = is_valid_texture(line, "SO");
		if (!game_mg->south)
			return (1);
		game_mg->parsed_flags[1] = 1;
		return (0);
	}
	return (-1);
}

int	parse_we_ea(t_map_mg *game_mg, char *line, int index)
{
	if (ft_strncmp(line, "WE ", 3) == 0 && !check_config_position(index))
	{
		if (game_mg->parsed_flags[2] != -1)
			return (display_error_direction(ERR_DUPLICATE_WE));
		game_mg->west = is_valid_texture(line, "WE");
		if (!game_mg->west)
			return (1);
		game_mg->parsed_flags[2] = 1;
		return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !check_config_position(index))
	{
		if (game_mg->parsed_flags[3] != -1)
			return (display_error_direction(ERR_DUPLICATE_EA));
		game_mg->east = is_valid_texture(line, "EA");
		if (!game_mg->east)
			return (1);
		game_mg->parsed_flags[3] = 1;
		return (0);
	}
	return (-1);
}

int	parse_colors(t_map_mg *game_mg, char *line, int index)
{
	if (ft_strncmp(line, "F ", 2) == 0 && !check_config_position(index))
	{
		if (game_mg->parsed_flags[4] != -1)
			return (display_error_color(ERR_DUPLICATE_FLOOR_COLOR));
		game_mg->floor_color = rgb_string_to_int(line);
		if (game_mg->floor_color == -1)
			return (display_error_color(ERR_INVALID_FLOOR_COLOR));
		game_mg->parsed_flags[4] = 1;
		free(line);
		return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !check_config_position(index))
	{
		if (game_mg->parsed_flags[5] != -1)
			return (display_error_color(ERR_DUPLICATE_CEIL_COLOR));
		game_mg->ceiling_color = rgb_string_to_int(line);
		if (game_mg->ceiling_color == -1)
			return (display_error_color(ERR_INVALID_CEIL_COLOR));
		game_mg->parsed_flags[5] = 1;
		free(line);
		return (0);
	}
	return (-1);
}

int	parse_line(t_map_mg *game_mg, char *line, int *i)
{
	int	ret;

	ret = 0;
	ret = parse_no_so(game_mg, line, *i);
	if (ret != -1)
		return (ret);
	ret = parse_we_ea(game_mg, line, *i);
	if (ret != -1)
		return (ret);
	ret = parse_colors(game_mg, line, *i);
	if (ret != -1)
		return (ret);
	return (parse_map_or_error(game_mg, line, i));
}
