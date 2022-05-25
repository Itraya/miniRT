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

double	contactsp(t_sp sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = vecdot(ray.direction, ray.direction);
	b = 2 * vecdot(vecsub(ray.origin, sphere.xyz), ray.direction);
	c = vecdot(vecsub(ray.origin, sphere.xyz), vecsub(ray.origin, sphere.xyz))
		- sphere.height * sphere.height;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	else
		return ((-b - sqrt(delta)) / (2 * a));
}

int	colortrgb(double t, double r, double g, double b)
{
	t *= 255.99;
	r *= 255.99;
	g *= 255.99;
	b *= 255.99;
	return ((int)t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

int	colorrgb(double r, double g, double b)
{
	int	t;

	t = 0;
	r *= 255.99;
	g *= 255.99;
	b *= 255.99;
	return (t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

double	raycolor(t_ray myray, t_var *p)
{
	double	t;
	t_vec	n;
	t_vec	unitdir;

	t = contactsp(p->sp[0], myray);
	if (t > 0)
	{
		n = vecunit(vecsub(vecat(myray, t), p->sp[0].xyz));
		return (0.5 * colorrgb(n.x + 1, n.y + 1, n.z + 1));
	}
	unitdir = vecunit(myray.direction);
	t = 0.5 * unitdir.y + 1;
	return ((1 - t) * colorrgb(1.0, 1.0, 1.0) + t * colorrgb(0.5, 0.7, 1.0));
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;

	myray.origin = p->c->xyz;
	myray.direction = newvec(y - p->data->winwidth / 2, x - p->data->winlength
			/ 2, -p->data->winwidth / (2 * tan((p->c->fov * M_PI / 180) / 2)));
	normalize(myray.direction);
	mypixelput(p->data, x, y, raycolor(myray, p));
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
