#include "../incl/miniRT.h"

void	vardef(t_data *data)
{
	data->winwidth = 960;
	data->winlength = 600 ;
}

int	closewin(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		closewin(data);
	return (0);
}

int	windowsop(t_var *p)
{
	t_data	data;

	p->data = &data;
	data.mlx = mlx_init();
	vardef(&data);
	data.win = mlx_new_window(data.mlx, data.winwidth, data.winlength, "baka");
	data.img = mlx_new_image(data.mlx, data.winwidth, data.winlength);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	generator(p);
	mlx_hook(data.win, 17, 1L << 2, closewin, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
