/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:43:11 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 15:31:21 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static char	*ft_strrchr(const char *s, int c)
{
	int	len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}

int	is_valid_arg(char *map_name)
{
	char	*map_exction;

	map_exction = ft_strrchr(map_name, '.');
	if (!map_exction)
		return (1);
	if (ft_strcmp(map_exction, ".cub") == 0)
		return (0);
	return (1);
}

char	*is_valid_texture(char *line, const char *id)
{
	char	*path;
	int		i;
	int		fd;

	if (!line || !id)
		return (display_error_input_malloc(ERR_NULL_INPUT, NULL), NULL);
	if (ft_strncmp(line, id, ft_strlen(id)) != 0
		|| line[ft_strlen(id)] != ' ')
		return (display_error_direction(ERR_INVALID_ID), NULL);
	i = ft_strlen(id);
	while (line[i] == ' ')
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (NULL);
	path[ft_strlen(path) - 1] = '\0';
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(path), \
		display_error_file(ERR_FILE_OPEN_FAILED, path), NULL);
	close(fd);
	free(line);
	line = NULL;
	return (path);
}

static int	check_zero_position(char **map, int row, int col)
{
	if (row == 0 || col == 0 || !map[row + 1] || map[row][col + 1] == '\0')
	{
		printf("Error: Open space at edge at (%d, %d)\n", row, col);
		return (1);
	}
	if (map[row][col + 1] == ' ' || \
		map[row][col - 1] == ' ' || \
		map[row + 1][col] == ' ' || \
		map[row - 1][col] == ' ')
	{
		printf("Error: Space next to open area at (%d, %d)\n", row, col);
		return (1);
	}
	return (0);
}

int	check_map_enclosure(char **map)
{
	int	row;
	int	col;

	if (!map || !*map)
	{
		print_error("Error: Map is empty or invalid.\n");
		return (1);
	}
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col] != '\0')
		{
			if (map[row][col] == '0')
				if (check_zero_position(map, row, col))
					return (1);
			col++;
		}
		row++;
	}
	return (0);
}
