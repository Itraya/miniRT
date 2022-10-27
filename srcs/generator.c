#include "../incl/miniRT.h"

//Lumière ambiante :Camera :Lumière :Sphere:Plan : Cylindre :
void	mypixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length + x
			* (data->bits_per_pixel * 0.125));
	if (y < data->winwidth && x < data->winlength)
	{
		//printf("%d %d - ",x, data->winlength);
		//printf("%d %d\n",y, data->winwidth);
		*(unsigned int *)dst = color;
	}
}

//int	setfacenormal(t_ray ray, t_vec outwardnormal, t_var *p)
//{
//	if (vecdot(ray.direction, outwardnormal) < 0)
//		p->hitrec.frontface = 1;
//	else
//		p->hitrec.frontface = 0;
//	if (p->hitrec.frontface == 1)
//		p->hitrec.normal = outwardnormal;
//	else
//		p->hitrec.normal = vecmult(outwardnormal, -1);
//}

/*
// a = vecdot(ray.direction, ray.direction);
// b = 2 * vecdot(vecsub(ray.origin, sphere.xyz), ray.direction);
// c = vecdot(vecsub(ray.origin, sphere.xyz), vecsub(ray.origin, sphere.xyz))
// 	- sphere.height * sphere.height;
// delta = b * b - 4 * a * c;
//i used a simplified version to be faster
//po intersection
//no normal
*/

double	contactsp(t_sp sphere, t_ray ray, t_var *p)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	root;

	a = vecnorm(ray.direction);
	b = vecdot(vecsub(ray.origin, sphere.xyz), ray.direction);
	c = vecnorm(vecsub(ray.origin, sphere.xyz)) - sphere.height * sphere.height;
	delta = b * b - a * c;
	if (delta < 0)
		return (0);
	if ((-b + sqrt(delta)) / a < 0)
		return (0);
	if ((-b - sqrt(delta)) / a > 0)
		root = (-b - sqrt(delta)) / a;
	else
		root = (-b + sqrt(delta)) / a;
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, root));
	p->data->no = getnormalized(vecsub(p->data->po, sphere.xyz));
	return (root);
}

double	contactpl(t_pl plane, t_ray ray, t_var *p)
{
	double	denom;
	double	t;

	denom = vecdot(plane.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(plane.xyz, ray.origin), plane.way) / denom;
	if (t < 0.000000001)
		return (0);
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
	p->data->no = plane.way;
	return (t);
}

double	contactcy(t_cy cyl, t_ray ray, t_var *p)
{
	// double	a;
	// double	b;
	// double	c;
	// double	delta;
	// double	root;
	// double	t1;
	// double	t2;
	// double	z1;
	// double	z2;

	// a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	// b = 2 * ray.direction.x * (ray.origin.x - cyl.xyz.x) + 2 * ray.direction.z * (ray.origin.z - cyl.xyz.z);
	// c = (ray.origin.x - cyl.xyz.x) * (ray.origin.x - cyl.xyz.x) + (ray.origin.z - cyl.xyz.z) * (ray.origin.z - cyl.xyz.z) - cyl.width * cyl.width;
	// delta = b * b - 4 * a * c;
	// if (delta < 0)
	// 	return (0);
	// t1 = (-1 * b - sqrt(delta)) / (2 * a);
	// t2 = (-1 * b + sqrt(delta)) / (2 * a);
	// z1 = ray.origin.y + t1 * ray.direction.y;
	// z2 = ray.origin.y + t2 * ray.direction.y;
	// dprintf(2, "z1 = %f, z2 = %f\n", z1, z2);
	// if (z1 < cyl.height + cyl.xyz.y && z1 > cyl.xyz.y)
	// 	root = t1;
	// else if (z2 < cyl.height + cyl.xyz.y && z2 > cyl.xyz.y)
	// 	root = t2;
	// else
	// 	return (0);

	// ----------------------------------

	double root;
	t_vec A = cyl.xyz;
	t_vec B = vecadd(cyl.xyz, vecmult(cyl.way, cyl.height));
	double R = cyl.width;
	t_vec d = getnormalized(vecsub(B, A));
	t_vec X = vecsub(ray.direction, vecmult(d, vecdot(ray.direction, d)));
	t_vec Y = vecsub(vecsub(ray.origin, A), vecmult(d, vecdot(vecsub(ray.origin, A), d)));
	float a = vecnorm(X);
	float b = 2 * vecdot(X, Y);
	float c = vecnorm(Y) - R * R;
	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	float sdelta = sqrt(delta);
	float t2 = (-b + sdelta) / (2 * a);
	if (t2 < 0)
		return (0);
	float t1 = (-b - sdelta) / (2 * a);
	if (t1 > 0)
		root = t1;
	else
		root = t2;
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, root));
	t_vec P = p->data->po;
	double len = cyl.height + 3;
	float dP = vecdot(vecsub(P, A), d);
	if (dP < 0 || dP > len)
		return (0);
	t_vec proj = vecadd(A, vecmult(d, dP));
	p->data->no = getnormalized(vecsub(P, proj));

	return (root);

	// ----------------------------------


	// double max = sqrt(pow(cyl.height / 2, 2) + pow(cyl.width, 2));
	// t_vec point = vecadd(ray.origin, vecmult(ray.direction, root));
	// t_vec length = vecsub(point, cyl.xyz);
	// if (vecnorm(length) > max)
	// 	root = t2;
	// point = vecadd(ray.origin, vecmult(ray.direction, root));
	// length = vecsub(point, cyl.xyz);
	// if (vecnorm(length) > max)
	// 	return (0);
}

int	colortrgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	colorrgb(int r, int g, int b)
{
	int	t;

	t = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}

double	goodlux(double num)
{
	if (num < 0)
		return (0);
	if (num > 255)
		return (255);
	return (num);
}

double	intershadow(t_ray myray, t_var *p)
{
	t_ray	rebund;
	int		i;
	double	dist;
	double	min_t;

	rebund.origin = vecadd(p->data->smpo, vecmult(p->data->smno, 0.01));
	rebund.direction = getnormalized(vecsub(p->l->xyz, p->data->smpo));
	i = 0;
	min_t = 99999999999999;
	while (p->sp[i].exist)
	{
		dist = contactsp(p->sp[i], rebund, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			p->data->shadowno = p->data->no;
			p->data->shadowpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->pl[i].exist)
	{
		dist = contactpl(p->pl[i], rebund, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			p->data->shadowno = p->data->no;
			p->data->shadowpo = p->data->po;
		}
		i++;
	}
	
	if (min_t * min_t > vecnorm(vecsub(p->l->xyz, p->data->shadowpo)))
		return (0.9);
	return (0.1);
}

double	returnluxa(t_vec lux, unsigned char *color, t_var *p)
{
	return (colorrgb(goodlux(lux.x + goodlux(p->a->rgb[0] * p->a->ratio \
	* color[0] / 255)), \
					goodlux(lux.y + goodlux (p->a->rgb[1] * p->a->ratio \
	* color[1] / 255)), \
					goodlux(lux.z + goodlux(p->a->rgb[2] * p->a->ratio \
	* color[2] / 255))));
}

double	raycolor(t_ray myray, double min_t, t_var *p, unsigned char *color)
{
	double	dist;
	t_vec	lux;

	lux = newvec(color[0], color[1], color[2]);
	p->data->depthmax--;
	if (min_t != 999999999999)
	{
		lux = vecmult(lux, intershadow(myray, p));
		lux = vecmult(lux, p->l->ratio * 50000 * goodlux(vecdot(\
		getnormalized(vecsub(p->l->xyz, p->data->smpo)), p->data->smno) \
		/ vecnorm(vecsub(p->l->xyz, p->data->smpo))));
		return (returnluxa(lux, color, p));
	}
	return (colorrgb(0, 0, 0));
}

void	assignrgb(unsigned char *dst, unsigned char *src)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dst[i] = src[i];
		i++;
	}
}

double contactdisk(t_cy cyl, t_ray ray, t_var *p)
{
	t_pl test;
	test.exist = 1;
	assignrgb(test.rgb, cyl.rgb);
	test.way = cyl.way;
	test.xyz = vecadd(cyl.xyz, vecmult(cyl.way, cyl.height));

	double	denom;
	double	t;

	denom = vecdot(test.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(test.xyz, ray.origin), test.way) / denom;
	if (t < 0.000000001)
		return (0);
	if (t)
	{
		t_vec v = vecsub(vecadd(ray.origin, vecmult(ray.direction, t)), test.xyz);
		double d2 = vecdot(v, v);
		// dprintf(2, "%f %f\n", sqrtf(d2), cyl.width);
		if (sqrtf(d2) <= cyl.width)
		{
			p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
			p->data->no = test.way;
			return (t);
		}
	}
	return (0);
}

double contactdisk2(t_cy cyl, t_ray ray, t_var *p)
{
	t_pl test;
	test.exist = 1;
	assignrgb(test.rgb, cyl.rgb);
	test.way = vecmult(cyl.way, -1);
	test.xyz = cyl.xyz;

	double	denom;
	double	t;

	denom = vecdot(test.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(test.xyz, ray.origin), test.way) / denom;
	if (t < 0.000000001)
		return (0);
	if (t)
	{
		t_vec v = vecsub(vecadd(ray.origin, vecmult(ray.direction, t)), test.xyz);
		double d2 = vecdot(v, v);
		// dprintf(2, "%f %f\n", sqrtf(d2), cyl.width);
		if (sqrtf(d2) <= cyl.width)
		{
			p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
			p->data->no = test.way;
			return (t);
		}
	}
	return (0);
}

double	inter(t_ray myray, t_var *p)
{
	int				i;
	unsigned char	rgb[3];
	double			min_t;
	double			dist;

	i = 0;
	min_t = 999999999999;
	while (p->sp[i].exist)
	{
		dist = contactsp(p->sp[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->sp[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->pl[i].exist)
	{
		dist = contactpl(p->pl[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->pl[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->cy[i].exist)
	{
		dist = contactcy(p->cy[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->cy[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->cy[i].exist)
	{
		dist = contactdisk(p->cy[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->cy[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->cy[i].exist)
	{
		dist = contactdisk2(p->cy[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->cy[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	return (raycolor(myray, min_t, p, rgb));
}

t_vec	getup(double z)
{
	if (z >= 0 && z <= 0.25)
		return (newvec(z/0.25, 1, 0));
	if (z >= 0.25 && z <= 0.5)
		return (newvec(1, 1 - (z - 0.25)/0.25, 0));
	if (z >= 0.5 && z <= 0.75)
		return (newvec(1, -1 + (z - 0.75)/0.25, 0));
	if (z >= 0.75 && z <= 1)
		return (newvec(1 - z, -1, 0));
	if (z <= 0 && z >= -0.25)
		return (newvec(z/0.25, 1, 0));
	if (z <= -0.25 && z >= -0.5)
		return (newvec(-1, 1 - (z + 0.25)/-0.25, 0));
	if (z <= -0.5 && z >= -0.75)
		return (newvec(-1, -1 - (z + 0.75)/-0.25, 0));
	if (z <= -0.75 && z >= -1)
		return (newvec(-1 - z, -1, 0));
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;
	int		i;
	double	color;

	myray.origin = p->c->xyz;
	myray.direction = newvec(x - p->data->winwidth / 2, y - p->data->winlength
			/ 2, (-p->data->winwidth / (2 * tan((p->c->fov * M_PI / 180) / 2))));
	normalize(myray.direction);
	double	z = p->c->way.z;
	p->c->way.z = 1;
	t_vec up = getup(z);
	t_vec cam_r = veccross(p->c->way, up);
	t_vec step1 = vecmult(cam_r, myray.direction.x);
	t_vec step2 = vecmult(up, myray.direction.y);
	t_vec step3 = vecmult(p->c->way, myray.direction.z);
	p->c->way.z = z;
	myray.direction = vecadd3(step1, step2, step3);
	i = 0;
	color = 0;
	while (i < p->data->sampleppix)
	{
		p->data->depthmax = 50;
		color += inter(myray, p);
		i++;
	}
	mypixelput(p->data, p->data->winwidth - x, y, color / p->data->sampleppix);
	//essayer de changer le sens soon
}

//i = H = x = len
//j = W = y = wid

void	generator(t_var *p)
{
	int	x;
	int	y;

	x = 0;
	while (x < p->data->winlength)
	{
		y = 0;
		while (y < p->data->winwidth)
		{
			algo(p, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
}
