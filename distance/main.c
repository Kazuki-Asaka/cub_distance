/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:40:05 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/15 18:53:37 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_map(t_cor *cor)
{
	int		fd;
	char	*str;
	int		i;
	int		j;

	i = 0;
	fd = open("map.cub", O_RDONLY);
	while (i < 5)
	{
		j = 0;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		while (j < 5)
		{
			// printf("print %c\n", str[j]);
			cor -> map[i][j] = str[j];
			j++;
		}
		i++;
	}
	// write(2, "a\n", 2);
	close(fd);
}

int	check_int_map(t_cor *cor, double x, double y)
{
	int	x_int;
	int	y_int;
	
	x_int = (int)x;
	y_int = (int)y;
	if (cor -> map[x_int][y_int] == '1')
		return (1);
	else
		return (0);
}

void	print_map(t_cor *cor)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			// printf("%d, %d\n", i, j);
			printf("%c ", cor -> map[i][j]);
		}
		printf("\n");
	}
}

void	culc_distance(double angle, t_cor *cor)
{
	double	dx;
	double	dy;
	t_start_cor a;
	t_start_cor b;
	int		tmp;
	
	dx = -tan(angle * M_PI / (double)180);
	dy = -1 / tan(angle * M_PI / (double)180);
	if (angle == (double)270)
	{
		a.init_x = cor->x_now;
		a.init_y = tmp;
		while(1)
		{
			if (a.init_x > (double)5 || a.init_x < (double)0 ||a.init_y > (double)5 || a.init_y < (double)0)
				break ;
			if (check_int_map(cor, a.init_x, a.init_y) == 1)
				break;
			a.init_y -= 1;
		}
	}
	else
	{
		tmp = (int)cor -> y_now;
		a.init_x = -(cor -> y_now -(double)tmp) / tan (angle * M_PI / (double)180);
		a.init_y = (double)tmp;
		tmp = (int)cor -> x_now + 1;
		b.init_x = tmp;
		b.init_y = -(cor -> x_now - (double)tmp) * tan(angle * M_PI / (double)180);
		printf("angle %f (%f, %f), (%f, %f)\n", angle, a.init_x, a.init_x, b.init_x, b.init_y);
		while(1)
		{
			if (a.init_x > (double)5 || a.init_x < (double)0 ||a.init_y > (double)5 || a.init_y < (double)0)
			{
				a.distance = a.init_x * cos((angle - (double)N) * M_PI / 180) + a.init_y * sin((angle - (double)N) * M_PI / 180);
				if (a.distance < 0)
					a.distance = -a.distance;
				break;
			}
			if (check_int_map(cor, a.init_x, a.init_y) == 1)
			{
				a.distance = a.init_x * cos((angle - (double)N) * M_PI / 180) + a.init_y * sin((angle - (double)N) * M_PI / 180);
				if (a.distance < 0)
					a.distance = -a.distance;
				break;
			}
			a.init_x = a.init_x + 1;
			a.init_y = a.init_y + dx;
		}
		while(1)
		{
			if (b.init_x > (double)5 || b.init_x < (double)0 ||b.init_y > (double)5 || b.init_y < (double)0)
			{
				b.distance = b.init_x * cos((angle - (double)N) * M_PI / 180) + b.init_y * sin((angle - (double)N) * M_PI / 180);
				if (b.distance < 0)
					b.distance = -b.distance;
				break;
			}
			if (check_int_map(cor, b.init_x, b.init_y) == 1)
			{
				b.distance = b.init_x * cos((angle - (double)N) * M_PI / 180) + b.init_y * sin((angle - (double)N) * M_PI / 180);
				if (b.distance < 0)
					b.distance = -b.distance;
				break;
			}
			b.init_x = b.init_x + dy;
			b.init_y = b.init_y + 1;
		}
		if (a.distance < b.distance)
			printf("distance %f\n", a.distance);
		else
			printf("distance %f\n", b.distance);
	}
}

void	culc_distance_loop(t_cor *cor)
{
	double	shift_angle;
	double	start_x;
	double	start_y;
	double	start_angle;
	double	finish_angle;
	double	i;

	shift_angle = (double)VIEW_ANGLE / (double)WIDTH;
	printf("shift angle %f\n", shift_angle);
	// printf("%f\n", (double)45 / (double)180);
	// printf("tan %f\n", tan((double)90 / (double)180 * M_PI));
	start_angle = (double)N - (double)VIEW_ANGLE / (double)2;//条件分岐が必要 構造体に持たせる（フックように）
	finish_angle = (double)N + (double)VIEW_ANGLE / (double)2;
	while(start_angle <= finish_angle)
	{
		culc_distance(start_angle, cor);
		start_angle += shift_angle;
	}
	// printf("angle %f\n", start_angle);
	
}

void	get_my_pos(t_cor *cor)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (cor -> map[i][j] != '0' && cor -> map[i][j] != '1')
			{
				cor -> direction = cor -> map[i][j];
				cor -> x_now = (double)i + 0.5;
				cor -> y_now = (double)j + 0.5;
			}
			j++;
		}
		i++;
	}
	printf("(%f, %f)\n", cor -> x_now, cor -> y_now);
}

int	main(void)
{
	t_cor	*cor;

	cor = malloc(sizeof(t_cor) * 1);
	if (cor == NULL)
		return (1);
	set_map(cor);
	print_map(cor);
	get_my_pos(cor);
	culc_distance_loop(cor);
}