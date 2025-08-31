/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:52 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 14:34:43 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	get_long_line_in_map(char **map)
{
	int	long_line;
	int	i;
	int	len;

	if (!map || !*map)
		return (0);
	long_line = 0;
	i = 0;
	len = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > long_line)
			long_line = len;
		i++;
	}
	return (long_line);
}

char	*copy_with_spaces(const char *src, int long_line)
{
	int		len;
	char	*dst;
	int		i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dst = malloc(long_line + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, len + 1);
	i = len;
	while (i < long_line)
	{
		dst[i] = ' ';
		i++;
	}
	dst[long_line] = '\0';
	return (dst);
}

int	remove_newline_chars(t_map_mg *game_mg)
{
	int	row;
	int	col;

	if (!game_mg || !game_mg->maps)
		return (1);
	row = 0;
	while (game_mg->maps[row])
	{
		col = 0;
		while (game_mg->maps[row][col])
		{
			if (game_mg->maps[row][col] == '\n')
				game_mg->maps[row][col] = '\0';
			col++;
		}
		row++;
	}
	return (0);
}

int	replace_map(t_map_mg *game_mg)
{
	int		long_line;
	char	**new_map;
	int		i;

	if (!game_mg || game_mg->map_hi <= 0 || !game_mg->maps)
		return (1);
	long_line = get_long_line_in_map(game_mg->maps);
	new_map = malloc(sizeof(char *) * (game_mg->map_hi + 1));
	if (!new_map)
		return (1);
	i = 0;
	remove_newline_chars(game_mg);
	while (game_mg->maps[i])
	{
		new_map[i] = copy_with_spaces(game_mg->maps[i], long_line);
		if (!new_map[i])
		{
			return (free_map(new_map), 1);
		}
		i++;
	}
	new_map[i] = NULL;
	free_map(game_mg->maps);
	game_mg->maps = new_map;
	return (0);
}
