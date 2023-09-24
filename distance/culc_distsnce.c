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
	return (cor -> map[y_int][x_int]);
}

char	check_map_y_axis(t_cor *cor, double x, double y, double angle)
{
	int	x_int;
	int	y_int;

	x_int = (int)x;
	y_int = (int)y;
	if ((double)90 < angle && angle < 270)
		x_int--;
	return (cor -> map[y_int][x_int]);
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
	double		tmp;

	dx = (int)cor -> x_now;
	dy = (int)cor -> y_now;
	if (((double)0 < angle && angle < (double)90)
	|| ((double)90 < angle && angle <(double)180))
		dy++;
	if (dy > cor -> y_now)
		tmp = (double)dy - cor -> y_now;
	else
		tmp = cor -> y_now - (double)dy;
	if (((double)180 < angle && angle < (double)270)
	|| ((double)270 < angle && angle <(double)360))
		tmp = -tmp;
	cor_init.init_y = (double)dy;
	cor_init.init_x = cor -> x_now + tmp / tan (angle * 3.14 / 180);
	return (cor_init);
}

t_state_cor	set_init_cor_y_axis(t_cor *cor, double angle)
{
	int			dx;
	int			dy;
	t_state_cor cor_init;
	double		tmp;

	dx = (int)cor -> x_now;
	dy = (int)cor -> y_now;
	if (((double)0 < angle && angle < (double)90)
	|| ((double)270 < angle && angle <(double)360))
		dx++;
	if ((double)dx > cor -> x_now)
		tmp =(double)dx - cor -> x_now;
	else
		tmp =  cor -> x_now - (double)dx;
	if (((double)90 < angle && angle < (double)180)
	|| ((double)180 < angle && angle <(double)270))
		tmp = -tmp;
	cor_init.init_x = (double)dx;
	cor_init.init_y = cor -> y_now + tmp * tan(angle * 3.14 / 180);
	return (cor_init);
}

int	init_check(t_state_cor cor_init)//マップによって異なる
{
	if (((double)0 <= cor_init.init_x && cor_init.init_x <= (double)5)
	&& ((double)0 <= cor_init.init_y && cor_init.init_y <= (double)5))
		return (0);
	else
		return (1);
}

t_state_cor	culc_intersection_x_axis(t_cor *cor, double angle)
{
	t_state_cor	cor_init;
	double		delta_y;
	double		tmp_distance;

	delta_y = set_delta_y(angle);
	cor_init = set_init_cor_x_axis(cor, angle);
	printf("angle %f x_axis_init (%f, %f)\n", angle, cor_init.init_x, cor_init.init_y);
	if (init_check(cor_init) == 1)
	{
		cor_init.distance = -1;
		return (cor_init);
	}
	while (check_map_x_axis(cor, cor_init.init_x, cor_init.init_y, angle) != '1')
	{
		cor_init.init_x = cor_init.init_x + delta_y;
		if (init_check(cor_init) == 1)
			break ;
		if (((double)0 < angle && angle < (double)90)
		|| ((double)90 < angle && angle < (double)180))
			cor_init.init_y ++;
		else
			cor_init.init_y--;
	}
	tmp_distance = sqrt((cor_init.init_x - cor -> x_now) * (cor_init.init_x - cor -> x_now) + (cor_init.init_y - cor -> y_now) * (cor_init.init_y - cor -> y_now));
	cor_init.distance = tmp_distance * cos((cor -> direction - angle) * 3.14 / (double)180); 
	return (cor_init);
}

t_state_cor	culc_intersection_y_axis(t_cor *cor, double angle)
{
	t_state_cor	cor_init;
	double		delta_x;
	double		tmp_distance;

	delta_x = set_delta_x(angle);
	cor_init = set_init_cor_y_axis(cor, angle);
	printf("angle %f y_axis_init (%f, %f)\n", angle, cor_init.init_x, cor_init.init_y);
	if (init_check(cor_init) == 1)
	{
		cor_init.distance = -1;
		return (cor_init);
	}
	while (check_map_y_axis(cor, cor_init.init_x, cor_init.init_y, angle) != '1')
	{
		cor_init.init_y = cor_init.init_y + delta_x;
		if (init_check(cor_init) == 1)
			break ;
		if (((double)0 < angle && angle < (double)90)
		|| ((double)270 < angle && angle < (double)360))
			cor_init.init_x ++;
		else
			cor_init.init_x--;
	}
	tmp_distance = sqrt((cor_init.init_x - cor -> x_now) * (cor_init.init_x - cor -> x_now) + (cor_init.init_y - cor -> y_now) * (cor_init.init_y - cor -> y_now));
	cor_init.distance = tmp_distance * cos((cor -> direction - angle) * 3.14 / (double)180);
	return (cor_init);
}

t_state_cor	multiple_parallel_intersection(t_cor *cor, double angle)
{
	t_state_cor	cor_init;
	int			x_int;

	x_int = cor -> x_now;
	cor_init.init_y = cor -> y_now;
	if (angle == (double) 0)
		x_int ++;
	cor_init.init_x = (double)x_int;
	printf("angle %f x_axis_init (%f, %f)\n", angle, cor_init.init_x, cor_init.init_y);
	while (check_map_y_axis(cor, cor_init.init_x, cor_init.init_y, angle) != '1')
	{
		if (angle == 0)
			cor_init.init_x = cor_init.init_x + (double)1;
		else
			cor_init.init_x = cor_init.init_x - (double)1;
	}
	if (angle == (double)0)
		cor_init.distance = cor_init.init_x - cor -> x_now;
	else
		cor_init.distance = cor_init.init_x;
	return (cor_init);
}

t_state_cor	multiple_vertical_intersection(t_cor *cor, double angle)
{
	t_state_cor	cor_init;
	int			y_int;

	y_int = cor -> y_now;
	cor_init.init_x = cor -> x_now;
	if (angle == (double) 90)
		y_int ++;
	cor_init.init_y = (double)y_int;
	printf("angle %f y_axis_init (%f, %f)\n", angle, cor_init.init_x, cor_init.init_y);
	while (check_map_x_axis(cor, cor_init.init_x, cor_init.init_y, angle) != '1')
	{
		if (angle == 90)
			cor_init.init_y = cor_init.init_y + (double)1;
		else
			cor_init.init_y = cor_init.init_y - (double)1;
	}
	if (angle == (double)270)
		cor_init.distance = cor -> y_now - cor_init.init_y;
	else
		cor_init.distance = cor_init.init_y;
	return (cor_init);
}

t_state_cor	choice_distance(t_state_cor x_axis, t_state_cor y_axis)
{
	if (x_axis.distance == -1)
		return (y_axis);
	if (y_axis.distance == -1)
		return (x_axis);
	if (x_axis.distance > y_axis.distance)
		return (y_axis);
	else
		return (x_axis);
}

void	step_position(t_cor *cor, double angle)
{
	t_state_cor	intersection_x_axis;
	t_state_cor	intersection_y_axis;
	t_state_cor	result_cor;

	if (angle == (double)0 || angle == (double)180)
	{
		intersection_y_axis = multiple_parallel_intersection(cor, angle);
		result_cor = intersection_y_axis;
		// printf("angle %f y_axis (%f, %f)\n", angle, intersection_y_axis.init_x, intersection_y_axis.init_y);
	}
	else if (angle == (double)90 || angle == (double)270)
	{
		intersection_x_axis = multiple_vertical_intersection(cor, angle);
		result_cor = intersection_x_axis;
		// printf("angle %f x_axis (%f, %f)\n", angle, intersection_x_axis.init_x, intersection_x_axis.init_y);
	}
	else
	{
		intersection_x_axis = culc_intersection_x_axis(cor, angle);
		intersection_y_axis = culc_intersection_y_axis(cor, angle);
		result_cor = choice_distance(intersection_x_axis, intersection_y_axis);
		// printf("angle %f x_axis (%f, %f) y_axis(%f, %f)\n", angle, intersection_x_axis.init_x, intersection_x_axis.init_y, intersection_y_axis.init_x, intersection_y_axis.init_y);
	}
	result_cor.angle = angle;
	printf("angle %f cor (%f, %f) distance %f\n", result_cor.angle, result_cor.init_x, result_cor.init_y, result_cor.distance);
}

void	culc_distance(t_cor *cor)
{
	double	shift_angle;
	double	start_angle;
	double	finish_angle;

	shift_angle = (double)VIEW_ANGLE / (double)WIDTH;
	start_angle = cor -> direction - (double)VIEW_ANGLE / (double)2;
	finish_angle = cor -> direction + (double)VIEW_ANGLE / (double)2;
	cor -> direction = (double)270;
	while (start_angle <= finish_angle)
	{
		step_position(cor, start_angle);
		start_angle += shift_angle;
	}
}