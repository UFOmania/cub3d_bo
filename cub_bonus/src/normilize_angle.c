/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normilize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:30 by massrayb          #+#    #+#             */
/*   Updated: 2025/08/28 12:49:31 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double	normilize_angle(double angle)
{
	if (angle >= 2 * M_PI)
		angle = fmod(angle, 2 * M_PI);
	return (angle);
}
