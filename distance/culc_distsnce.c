/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   culc_distsnce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:37:40 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/22 17:06:46 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	check_map_x_axis(t_cor *cor, double x, double y, double angle)
{
	int	x_int;
	int	y_int;

	x_int = (int)x;
	y_int = (int)y;
	if ((double)180 < angle && angle < (double)360)
		y_int--;
	return (cor -> map[x_int][y_int]);
}

char	check_map_y_axis(t_cor *cor, double x, double y, double angle)
{
	int	x_int;
	int	y_int;

	x_int = (int)x;
	y_int = (int)y;
	if ((double)90 < angle && angle < 270)
		x_int--;
	return (cor -> map[x_int][y_int]);
}

double	set_delta_x(double angle)
{
	double	delta_x;

	delta_x = tan (angle * 3.14 / (double)180);
	if (((double)90 < angle && angle < (double)180)
	|| ((double)180 < angle && angle < (double)270))
		delta_x = - delta_x;
	return (delta_x);
}

double	set_delta_y(double angle)
{
	double	delta_y;

	delta_y = (double)1 / tan (angle * 3.14 / 180);
	if (((double)180 < angle && angle < (double)270)
	|| ((double)270 < angle && angle < (double)360))
		delta_y = - delta_y;
	return (delta_y);
}

t_state_cor	set_init_cor_x_axis(t_cor *cor, double angle)
{
	int			dx;
	int			dy;
	t_state_cor cor_init;
	double	tmp;

	dx = cor -> x_now;
	dy = cor -> y_now;
	if (((double)0 < angle && angle < (double)90)
	|| ((double)90 < angle && angle <(double)180))
		dy++;
	if (dy > tmp)
		tmp = dy - cor -> y_now;
	else
		tmp = cor -> y_now - dy;
	if (((double)90 < angle && angle < (double)180)
	|| ((double)270 < angle && angle <(double)360))
		tmp = -tmp;
	cor_init.init_y = (double)dy;
	cor_init.init_x = cor -> x_now + tmp / tan (angle * 3.14 / 180);
}

t_state_cor	culc_intersection_x_axis(t_cor *cor, double angle)
{
	t_state_cor	cor_init;
	double		delta_y;

	delta_y = set_delta_y(angle);
	cor_init = set_init_cor_x_axis(cor, angle);
	
}

t_state_cor	culc_intersection_y_axis(t_cor *cor, double angle)
{
	t_state_cor	cor_init;
	double		delta_x;

	delta_x = set_delta_x(angle);
}

void	step_position(t_cor *cor, double angle)
{
	t_state_cor	intersection_x_axis;
	t_state_cor	intersection_y_axis;

	if (angle / (double)90 == 0)
		multiple_ninty_inertaction(cor, angle);
	else
	{
		intersection_x_axis = culc_intersection_x_axis(cor, angle);
		intersection_y_axis = culc_intersection_y_axis(cor, angle);
	}
}

void	culc_distance(t_cor *cor)
{
	double	shift_angle;
	double	start_angle;
	double	finish_angle;

	shift_angle = (double)VIEW_ANGLE / (double)WIDTH;
	start_angle = cor -> direction - (double)VIEW_ANGLE / (double)2;
	finish_angle = cor -> direction + (double)VIEW_ANGLE / (double)2;
	while (start_angle <= finish_angle)
	{
		step_position(cor, start_angle);
		start_angle += shift_angle;
	}
}