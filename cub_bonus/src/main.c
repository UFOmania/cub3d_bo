 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:23 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/30 15:54:32 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"


void play_music(void)
{
    system("afplay music/price-of-freedom-33106.mp3 &");   // macOS
    // system("mpg123 -q music.mp3 &"); // Linux
}

void stop_music(void)
{
    system("killall afplay"); // macOS - this kills the 'afplay' process
    // system("killall mpg123"); // Linux
}

//void mlx_mouse_hide(void *mlx_ptr, void *win_ptr);
void	lanch_engine(t_game *game)
{
	mlx_close_hook(game->mlx, close_game, game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(game->mlx, input, game);
		// mouse click
	mlx_mouse_hook(game->mlx, catch_mouse_click, game);

	// mouse move
	mlx_cursor_hook(game->mlx, catch_mouse_move, game);
	mlx_loop_hook(game->mlx, update, game);
	play_music();
	mlx_loop(game->mlx);

}
void f()
{
	system("leaks -q cub");
	system("lsof -c cub");
}

int	main(int ac, char **av)
{
	atexit(f);
	t_game	game;

	game = (t_game){0};
	if (ac != 2)
		return (display_error_arg(ERR_EXPECTED_ONE_ARG));
	if (is_valid_arg(av[1]))
		return (display_error_arg(ERR_INVALID_ARGUMENT));
	game.mlx = mlx_init(WIDTH, HEIGHT, "gta VI", 0);
	if (!game.mlx)
		return (mlx_strerror(mlx_errno), EXIT_FAILURE);
	if (init_game(&game, av[1]) == R_FAIL)
		return (1);
	lanch_engine(&game);
}
