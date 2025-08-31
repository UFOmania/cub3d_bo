/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:32 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 14:34:36 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parse_rgb_component(const char *str)
{
	int	value;
	int	i;

	if (!str || !*str || str[0] == '-')
		return (-1);
	value = 0;
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (-1);
		i++;
	}
	return (value);
}

static void	assign_rgb_value(int channel, int value, t_parsing_rgba *rgba)
{
	if (channel == 0)
		rgba->r = value;
	else if (channel == 1)
		rgba->g = value;
	else if (channel == 2)
		rgba->b = value;
}

static int	read_component(const char *str, int *i, int channel,
		t_parsing_rgba *rgba)
{
	int	value;

	value = parse_rgb_component(str + *i);
	if (value < 0 || value > 255)
		return (-1);
	assign_rgb_value(channel, value, rgba);
	while (ft_isdigit((unsigned char)str[*i]))
		(*i)++;
	return (0);
}

static int	extract_rgb_components(const char *str, t_parsing_rgba *rgba)
{
	int	channel;
	int	i;
	int	spe;

	channel = 0;
	i = 0;
	spe = 0;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			spe++;
		if (ft_isdigit((unsigned char)str[i]))
		{
			if (read_component(str, &i, channel, rgba) == -1)
				return (-1);
			channel++;
		}
		else
			i++;
	}
	if (channel != 3 || spe != 3)
		return (-1);
	return (0);
}

int	rgb_string_to_int(const char *color_str)
{
	t_parsing_rgba	rgba;

	if (!color_str)
		return (-1);
	rgba.i = 0;
	if (color_str[0] == 'F' || color_str[0] == 'C')
		rgba.i++;
	while (color_str[rgba.i] && color_str[rgba.i] == ' ')
		rgba.i++;
	if (extract_rgb_components(color_str + rgba.i, &rgba) == -1)
		return (-1);
	return ((rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | 255);
}
