/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:59:46 by ybassour          #+#    #+#             */
/*   Updated: 2025/08/30 15:41:02 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

# define ERR_MALLOC_FAILED            1
# define ERR_CANNOT_OPEN_FILE         2
# define ERR_NULL_MAP_NAME            3
# define ERR_INVALID_MAP_SIZE         4
# define ERR_DUPLICATE_NO             5
# define ERR_DUPLICATE_SO             6
# define ERR_DUPLICATE_WE             7
# define ERR_DUPLICATE_EA             8
# define ERR_DUPLICATE_FLOOR_COLOR    9
# define ERR_INVALID_FLOOR_COLOR      10
# define ERR_DUPLICATE_CEIL_COLOR     11
# define ERR_INVALID_CEIL_COLOR       12
# define ERR_STRDUP_FAILED            13
# define ERR_INVALID_MAP_CONFIG       14
# define ERR_EXPECTED_ONE_ARG         15
# define ERR_INVALID_ARGUMENT         16
# define ERR_PROCESSING_MAP           16
# define ERR_NULL_INPUT 17
# define ERR_INVALID_ID 18
# define ERR_FILE_OPEN_FAILED 20

typedef struct s_map_mg
{
	char	**maps;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		ceiling_color;
	int		floor_color;
	int		map_hi;
	char	player_seen;
	int		player_pos[2];
	int		player_count;
	int		parsed_flags[12];
}	t_map_mg;

typedef struct s_parsing_rgba
{
	int	r;
	int	g;
	int	b;
	int	i;
}	t_parsing_rgba;

int		is_valid_arg(char *map_name);
bool	is_has_space_one_zero(char *line);
int		rgb_string_to_int(const char *color_str);
bool	is_valid_config_count(t_map_mg *game_mg);
int		init_parsed_flags(t_map_mg *game_mg);
bool	validate_game_mg(t_map_mg *game_mg);
void	prin_deb(t_map_mg *game_mg);
int		init_parsed_flags(t_map_mg *game_mg);
int		init_floor_color(t_map_mg *game_mg);
void	free_map_mg(t_map_mg *game_mg);
int		init_map_mg(t_map_mg *game_mg);
int		parse_line(t_map_mg *game_mg, char *line, int *i);
int		is_valid_map(t_map_mg *game_mg);
int		replace_map(t_map_mg *game_mg);
int		check_player_in_map(t_map_mg *game_mg);
int		apply_map_ope(char *map_name, t_map_mg *game_mg);
char	*is_valid_texture(char *line, const char *id);
int		check_map_enclosure(char **map);
void	free_map(char **map);
void	putstr_fd(const char *s, int fd, int boolean);
void	print_error(const char *msg);
void	print_error2(const char *msg, const char *detail);
int		display_error_direction(int code);
int		display_error_file(int code, const char *target);
int		display_error_arg(int code);
int		display_error_input_malloc(int code, const char *target);
int		display_error_color(int code);
void	print_error2(const char *msg, const char *detail);
void	print_error(const char *msg);
int		parse_map_or_error(t_map_mg *game_mg, char *line, int *i);
int		ft_strcmp(const char *s1, const char *s2);
int		check_player_validity(char **maps);
int		player_adjacent_to_space(char **maps, int row, int col);
int		is_player_symbol(char c);
#endif