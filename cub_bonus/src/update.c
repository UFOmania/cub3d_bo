/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:40 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 12:49:41 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	apply_inputs(&game->player, game->map);
	raycast(game);
}
