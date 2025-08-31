/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:45 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 19:38:42 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <math.h>

# include "MLX42.h"
# include "parsing.h"
# include "libft.h"
# include <time.h>

# define R_FAIL 0
# define R_SUCCESS 1

# define WIDTH 800.0
# define HEIGHT 600.0
# define FOV 50.0
# define TILE_SIZE 100.0
# define MOVE_SPEED 10.0
# define PLAYER_RADIUS 15.0
# define ROT_SPEED 0.1

# define HORIZONTAL 1
# define VERTICAL 2
# define N 0
# define S 1
# define W 2
# define E 3

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec2	hit_pos;
	double	len;
	double	ray_angle;
	int		tex_hit_side;
}	t_ray;

typedef struct s_player
{
	t_vec2	pos;
	double	angle;
	int		go_right;
	int		go_up;
	int		rotate_right;
    int mouse_down;
	int is_over_gang;
	double dir_x;    // direction vector x
	double dir_y;    // direction vector y
	double plane_x;  // camera plane x
	double plane_y;  // camera plane 
}	t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	mlx_image_t		*texture[4];
	char			**map;
	double			ppd;
	int				floor_color;
	int				ceiling_color;
}	t_game;

typedef struct s_raycast_args
{
	int		y_on_screen;
	int		x_on_screen;
	int		tex_x;
	int		tex_y;
	double	wall_h;
	double	margen;
	t_ray	ray;
}	t_raycast_args;

void			input(mlx_key_data_t keydata, void *param);
void			close_game(void *param);
void			update(void *param);
void			apply_inputs(t_player *player, char **map);

//init
int				init_game(t_game *game, char *map_name);
int				load_textures(t_game *game, t_map_mg *mg);

//raycast
t_ray			cast_ray(t_game *game, t_vec2 pos, double aray_angle);
void			raycast(t_game *game);
void			do_render(t_game *game, t_raycast_args *a);

//utils
double			deg_to_rad(double deg);
double			normilize_angle(double angle);
int				get_rgba(int r, int g, int b, int a);
double			distance(t_vec2 a, t_vec2 b);
unsigned int	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void			clear_game(t_game *game);
///
void	catch_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void *param);

void	catch_mouse_move(double xpos, double ypos, void *param);
void  stop_music(); 
#endif