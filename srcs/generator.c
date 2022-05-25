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
	t_vec	sphereorig;
	double	delta;

	sphereorig = newvec(sphere.xyz[0], sphere.xyz[1], sphere.xyz[2]);
	a = vecdot(ray.direction, ray.direction);
	b = 2 * vecdot(vecsub(ray.origin, sphereorig), ray.direction);
	c = vecdot(vecsub(ray.origin, sphereorig), vecsub(ray.origin, sphereorig))
		- sphere.height * sphere.height;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	else
		return ((-b - sqrt(delta)) / (2 * a));
}

int	colortrgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	raycolor(t_ray myray, t_var *p)
{
	double	t;
	double	n;
	t_vec	sphereorig;

	sphereorig = newvec(p->sp[0].xyz[0], p->sp[0].xyz[1], p->sp[0].xyz[2]);
	t = contactsp(p->sp[0], myray);
	if (t > 0)
	{
		lenvec = veclen(vecsub(vecat(myray, t), sphereorig));
	}
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;

	myray.origin = newvec(p->c->xyz[0], p->c->xyz[1], p->c->xyz[2]);
	myray.direction = newvec(y - p->data->winwidth / 2, x - p->data->winlength
			/ 2, -p->data->winwidth / (2 * tan((p->c->fov * M_PI / 180) / 2)));
	normalize(myray.direction);
	//if (contactsp(p->sp[0], myray) > 0)
	//{
	//	mypixelput(p->data, x, y, colortrgb(0, 250, 0, 0));
	//}
	//else
	//{
	//	mypixelput(p->data, x, y, colortrgb(0, 255, 255, 255));
	//}
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
