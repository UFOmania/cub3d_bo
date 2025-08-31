/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:11:09 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 15:36:15 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	get_size(const char *map_file)
{
	int		len;
	int		fd;
	char	*line;

	len = 0;
	if (!map_file)
		return (-1);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		display_error_file(ERR_CANNOT_OPEN_FILE, map_file);
		return (-1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_has_space_one_zero(line))
			len++;
		free(line);
	}
	close(fd);
	return (len);
}

int	loop_read_map(t_map_mg *game_mg, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (parse_line(game_mg, line, &i))
		{
			free(line);
			close(fd);
			game_mg->maps[i] = NULL;
			return (1);
		}
	}
	game_mg->maps[i] = NULL;
	return (0);
}

int	open_map(char *map_name, t_map_mg *game_mg)
{
	int	fd;
	int	size;
	int	vl;

	size = get_size(map_name);
	game_mg->map_hi = size;
	if (!map_name)
		return (display_error_file(ERR_NULL_MAP_NAME, NULL));
	if (size == -1)
		return (1);
	if (size <= 0)
		return (display_error_file(ERR_INVALID_MAP_SIZE, NULL), 1);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (display_error_file(ERR_CANNOT_OPEN_FILE, map_name));
	game_mg->maps = malloc(sizeof(char *) * (size + 1));
	if (!game_mg->maps)
	{
		close(fd);
		return (display_error_input_malloc(ERR_MALLOC_FAILED, NULL));
	}
	vl = loop_read_map(game_mg, fd);
	close(fd);
	return (vl);
}

int	apply_map_ope(char *map_name, t_map_mg *game_mg)
{
	if (open_map(map_name, game_mg))
	{
		free_map_mg(game_mg);
		return (1);
	}
	if (!is_valid_config_count(game_mg) || !validate_game_mg(game_mg))
	{
		free_map_mg(game_mg);
		return (display_error_file(ERR_INVALID_MAP_CONFIG, NULL));
	}
	if (replace_map(game_mg))
	{
		return (free_map_mg(game_mg), 1);
	}
	if (check_player_in_map(game_mg))
	{
		return (free_map_mg(game_mg), 1);
	}
	if (check_map_enclosure(game_mg->maps))
	{
		return (free_map_mg(game_mg), 1);
	}
	return (0);
}
