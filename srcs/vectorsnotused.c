/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorsnotused.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:58:30 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/09 13:47:24 by mlagrang         ###   ########.fr       */
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

t_vec	vec_rotate(t_vec vec, t_vec a, float theta)
{
	t_vec	res;

	res.x = a.x * (a.x * vec.x + a.y * vec.y + a.z * vec.z) * (1 - cos(theta))
		+ vec.x * cos(theta)
		+ (-a.z * vec.y + a.y * vec.z) * sin(theta);
	res.y = a.y * (a.x * vec.x + a.y * vec.y + a.z * vec.z) * (1 - cos(theta))
		+ vec.y * cos(theta)
		+ (a.z * vec.x - a.x * vec.z) * sin(theta);
	res.z = a.z * (a.x * vec.x + a.y * vec.y + a.z * vec.z) * (1 - cos(theta))
		+ vec.z * cos(theta)
		+ (-a.y * vec.x + a.x * vec.y) * sin(theta);
	return (res);
}

t_vec	vec_rotate_y(t_vec vec, float theta)
{
	t_vec	res;

	res.x = vec.x * cos(theta) + vec.z * sin(theta);
	res.y = vec.y;
	res.z = -vec.x * sin(theta) + vec.z * cos(theta);
	return (res);
}
