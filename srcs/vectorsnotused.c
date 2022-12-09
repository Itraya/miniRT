/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorsnotused.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:58:30 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/09 16:02:27 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_vec	vecat(t_ray ray, double t)
{
	return (vecadd(ray.origin, vecmult(ray.direction, t)));
}

t_vec	vecunit(t_vec v1)
{
	return (vecdiv(v1, veclen(v1)));
}

double	veclen(t_vec v1)
{
	return (sqrt(vecnorm(v1)));
}

t_vec	vecdiv(t_vec v1, double mult)
{
	t_vec	new;

	new = vecmult(v1, 1 / mult);
	return (new);
}

t_vec	met_a_un(t_vec v1)
{
	double	mult;

	if (v1.x >= v1.y && v1.x >= v1.z)
		mult = v1.x;
	if (v1.y >= v1.x && v1.y >= v1.z)
		mult = v1.y;
	if (v1.z >= v1.x && v1.z >= v1.y)
		mult = v1.z;
	v1.x /= mult;
	v1.y /= mult;
	v1.z /= mult;
	return (v1);
}
