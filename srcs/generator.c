#include "../incl/miniRT.h"

//Lumière ambiante :Camera :Lumière :Sphere:Plan : Cylindre :
void	mypixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length + x
			* (data->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

int	colortrgb(double t, double r, double g, double b)
{
	t *= 255.99;
	r *= 255.99;
	g *= 255.99;
	b *= 255.99;
	return ((int)t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

int	contactsp(t_sp *sphere, t_ray ray)
{
	double a = 1;
	double b = 2 * vecdot() //video 42;20
}

void	algo(t_var *p, int x, int y)
{
	t_ray	*ray;

	ray.x = (double)x;
	ray.y = (double)y;
	ray.z = 0;
	if (p->sp[0].exist == 1)
	{
		if (x - p->data->winwidth / 2 )
	}
	mypixelput(p->data, x, y, colortrgb(0, (double)x / p->data->winwidth, (double)y / p->data->winlength, 0.2));

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
