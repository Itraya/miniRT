#include "../incl/miniRT.h"

//Lumière ambiante :Camera :Lumière :Sphere:Plan : Cylindre :
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length + x
			* (data->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

int	create_trgb(double t, double r, double g, double b)
{
	t *= 255.99;
	r *= 255.99;
	g *= 255.99;
	b *= 255.99;
	return ((int)t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
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
			my_mlx_pixel_put(p->data, x, y, create_trgb(0, (double)x / p->data->winwidth, (double)y / p->data->winlength, 0.2));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
} 
