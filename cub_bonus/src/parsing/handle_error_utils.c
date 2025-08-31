/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:05:31 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 15:39:26 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	putstr_fd(const char *s, int fd, int boolean)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	if (boolean)
		write(fd, "\n", 1);
}

void	print_error(const char *msg)
{
	putstr_fd(msg, 2, 1);
}

void	print_error2(const char *msg, const char *detail)
{
	putstr_fd(msg, 2, 0);
	putstr_fd(detail, 2, 1);
}

int	display_error_direction(int code)
{
	if (code == ERR_DUPLICATE_NO)
		print_error("Error: Duplicate NO\n");
	else if (code == ERR_DUPLICATE_SO)
		print_error("Error: Duplicate SO\n");
	else if (code == ERR_DUPLICATE_WE)
		print_error("Error: Duplicate WE\n");
	else if (code == ERR_DUPLICATE_EA)
		print_error("Error: Duplicate EA\n");
	else if (code == ERR_INVALID_ID)
		print_error("Error: invalid texture identifier\n");
	else
		return (0);
	return (1);
}

int	parse_map_or_error(t_map_mg *game_mg, char *line, int *i)
{
	int	j;

	if (line[0] == '\n' && *i <= 0)
	{
		free (line);
		line = NULL;
		return (0);
	}
	if (is_has_space_one_zero(line))
	{
		j = *i;
		game_mg->maps[j] = line;
		if (!game_mg->maps[j])
			return (display_error_input_malloc(ERR_NULL_INPUT, NULL), 1);
		j++;
		*i = j;
		return (0);
	}
	return (1);
}
