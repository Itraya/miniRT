/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:09 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/14 13:57:05 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

double	square(double t)
{
	return (t * t);
}

double	contactco(t_co con, t_ray ray, t_var *p)
{
	return (0);
	// t_vec B = vecadd(con.xyz, vecmult(con.way, con.height));
	// t_vec d = getnormalized(vecsub(B, con.xyz));
	// t_vec	D = ray.direction;
	// t_vec	O = ray.origin;
	// t_vec	C = con.xyz;
	// t_vec	V = con.way;
	// t_vec	CO = vecsub(O, C);
	// double	a = square(vecdot(D, V)) - square(cos(con.angle));
	// double	b = 2 * (vecdot(D, V) * vecdot(CO, V)) - vecdot(D, CO) * square(cos(con.angle));
	// double	c = square(vecdot(CO, V)) - vecdot(CO, CO) * square(cos(con.angle));
	// double	delta = b * b - 4 * a * c;
	// if (delta < 0)
	// 	return (0);
	// delta = sqrt(delta);
	// double	t1 = (-b - delta) / (2 * a);
	// double	t2 = (-b + delta) / (2 * a);
	// double	root = t2;
	// if (t2 < 0)
	// 	root = t1;
	// if (root < 0)
	// 	return (0);
	// t_vec P = vecadd(ray.origin, vecmult(ray.direction, root));
	// if (vecdot(vecsub(P, C), V) <= 0)
	// 	return (0);
	// p->data->po = vecadd(ray.origin, vecmult(ray.direction, root));
	// double	dp = vecdot(vecsub(p->data->po, con.xyz), d);
	// if (dp < 0 || dp > con.height)
	// 	return (0);
	// p->data->no = getnormalized(vecsub(p->data->po,
	// 			vecadd(con.xyz, vecmult(d, dp))));
	// // dprintf(2, "%d	%d\n", p->x, p->y);
	// return (root);

	t_vec	v = ray.direction;
	t_vec	C = con.xyz;
	t_vec	H = vecadd(C, vecmult(con.way, con.height));
	double	r = con.angle;
	t_vec	h = vecsub(C, H);
	t_vec	hh = vecdiv(h, vecnorm(h));
	double	m = square(r) / square(vecnorm(h));
	t_vec	w = vecsub(ray.origin, H);

	double	a = vecdot(v, v) - m * square(vecdot(v, h)) - square(vecdot(v, h));
	double	b = 2 * (vecdot(v, w) - m * vecdot(v, h) * vecdot(w, h) - vecdot(v, h) * vecdot(w, h));
	double	c = vecdot(w, w) - m * square(vecdot(w, h)) - square(vecdot(w, h));
	double	delta = b * b - 4.0 * a * c;
	if (delta < 0)
		return (0);
	delta = sqrt(delta);
	double	root = (-b - delta) / (2 * a);
	if (root < 0)
		root = (-b + delta) / (2 * a);
	if (root < 0)
		return (0);
	t_vec L = vecadd(ray.origin, vecmult(ray.direction, root));
	// if (vecdot(vecsub(L, H), hh) > vecnorm(h) || vecdot(vecsub(L, H), hh) < 0)
	// 	return (0);
	if (vecdot(vecsub(L, H), hh) < 0)
		return (0);
	// if (vecdot(vecsub(L, H), hh) > vecnorm(h))
	// 	return (0);
	return (root);
}

double	inter_co(t_var *p, t_ray myray, double min_t, unsigned char rgb[3])
{
	int		i;
	double	dist;

	dist = contactco(p->co[0], myray, p);
	if (dist && dist * dist < min_t)
	{
		assignrgb(rgb, p->co[0].rgb);
		p->data->smno = p->data->no;
		p->data->smpo = p->data->po;
	}
	return (dist);
}

int	ft_malloc_co(t_var *p, char **lines)
{
	t_co	*fig;

	fig = malloc(2 * sizeof(t_co));
	fig[0].exist = 1;
	fig[0].xyz = newvec(-40, 40, 50);
	fig[0].way = newvec(0, 1, 0);
	fig[0].height = 40;
	// fig[0].angle = (30 / 360) * M_PI * 2;
	fig[0].angle = 20;
	fig[0].rgb[0] = 255;
	fig[0].rgb[1] = 255;
	fig[0].rgb[2] = 255;
	fig[1].exist = 0;
	p->co = fig;
	return (1);
}
