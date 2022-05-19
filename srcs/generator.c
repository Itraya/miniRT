#include "../incl/miniRT.h"

//Lumière ambiante :Camera :Lumière :Sphere:Plan : Cylindre :
void	mypixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length + x
			* (data->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

int	colortrgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
} 

int	contactsp(t_sp sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	t_vec	sphereorigin;
	double	delta;

	sphereorigin.x = sphere.xyz[0];
	sphereorigin.y = sphere.xyz[1];
	sphereorigin.z = sphere.xyz[2];
	a = 1;
	b = 2 * vecdot(ray.direction, vecsub(ray.origin, sphereorigin));
	c = vecnorm(vecsub(ray.origin, sphereorigin)) - sphere.height * sphere.height;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	if (((-b + sqrt(delta)) / (2 * a)) > 0)
		return (1);
	return (0);
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;

	myray.origin.x = p->c->xyz[0];
	myray.origin.y = p->c->xyz[1];
	myray.origin.z = p->c->xyz[2];
	myray.direction.x = x - p->data->winwidth / 2;
	myray.direction.y = y - p->data->winlength / 2;
	myray.direction.z = -p->data->winlength / (2 * tan((p->c->fov * M_PI / 180) / 2));
	normalize(myray.direction);
	if (contactsp(p->sp[0], myray) == 1)
	{
		mypixelput(p->data, x, y, colortrgb(0, 255, 0, 0));
	}
	else
		mypixelput(p->data, x, y, colortrgb(0, 255, 255, 255));
}

void	generator(t_var *p)
{
	int	x;
	int	y;

	y = 0;
	while (y < p->data->winlength)
	{
		x = 0;
		while (x < p->data->winwidth)
		{
			algo(p, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
}
