/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:37:42 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/21 16:26:52 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "get_next_line.h"

#define WIDTH 1920
#define HEIGHT 1080
#define VIEW_ANGLE 120
#define N	270
#define E	0
#define S	90
#define	W	180

typedef struct s_cor
{
	double	x_now;
	double	y_now;
	double	direction;
	char	map[5][5];
} t_cor;

typedef struct s_state_cor
{
	double	init_x;
	double	init_y;
	double	distance;
} t_state_cor;

#endif