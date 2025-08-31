/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:13 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 19:55:46 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
/// @brief 
/// @param keydata 
/// @param game

void catch_mouse_move(double xpos, double ypos, void *param)
{
    t_game *game = param;
    static double last_x = -1;
    int win_width = WIDTH;
    int win_height = HEIGHT;

	 // Check if mouse is outside window
    if (xpos < 0 || xpos > win_width || ypos < 0 || ypos > win_height)
    {
        last_x = -1; // reset last_x to avoid a huge delta when mouse comes back
        game->player.rotate_right = 0; // stop rotation
        return;
    }
    // First frame
    if (last_x < 0)
    {
        last_x = xpos;
        return;
    }

    double delta_x = xpos - last_x;
    double sensitivity = 0.1;

    game->player.rotate_right = delta_x * sensitivity;

    // Recenter mouse to middle of window
    int center_x = win_width / 2;
    int center_y = win_height / 2;
    mlx_set_mouse_pos(game->mlx, center_x, center_y);

    last_x = center_x; // update last_x to center
}

void play_music_atck(void)
{
    system("afplay music/g36-e-fire-88029.mp3 &");   // macOS
    // system("mpg123 -q music/war-99133.mp3 &"); // Linux
}

void stop_music_atck(void)
{
    system("killall afplay"); // macOS
    // system("killall mpg123"); // Linux
}


int is_over_gang(void *param)
{
	t_game	*game;

	game = (t_game *)param;
    if (game->player.is_over_gang <= 0)
        return 0; // Mouse is over the gang
	game->player.is_over_gang--;
    return 1;
}
int increamte_gnag_shoot(void *param)
{
	t_game	*game;
	int time_;
	game = (t_game *)param;
	if (game->player.is_over_gang <= 0)
	{
		time_ = (int) mlx_get_time();
		if (time_ % 2 == 0)
		{
			printf("enmtion update\n\n");
			game->player.is_over_gang = 10;
		}
	}
    return (1);
}
void catch_mouse_click(mouse_key_t button, action_t action,
                       modifier_key_t mods, void *param)
{
    (void)mods;
    (void)param;

	 if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
    {
        // Suppose is_over_gang() checks if the click is on a gang
       if (is_over_gang( param))
            play_music_atck();
		else
			increamte_gnag_shoot(param);
	}
   
}

static void	catch_key_press(mlx_key_data_t keydata, t_game *game)
{
	printf("Key pressed: %d\n", keydata.key);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player.go_up = 1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->player.go_up = -1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->player.go_right = -1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->player.go_right = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player.rotate_right = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player.rotate_right = 1;
		
}

static void	catch_key_release(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->player.go_up = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->player.go_up = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->player.go_right = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->player.go_right = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player.rotate_right = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player.rotate_right = 0;
}

void	input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_game(param);
	catch_key_press(keydata, game);
	catch_key_release(keydata, game);

}

void	close_game( void *param)
{
	t_game	*game;

	game = (t_game *)param;
	 stop_music(); 
	clear_game(game);
}
