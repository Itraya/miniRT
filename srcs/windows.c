/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:57:30 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/16 13:52:53 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

void	vardef(t_data *data)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	data->winwidth = 1000;
	data->winlength = data->winwidth;
	data->sampleppix = 1;
	data->depthmax = 50;
}

int	closewin(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook2(int keycode, t_var *p)
{
	if (keycode == 40 && p->l->ratio != 0)
		p->l->ratio = 0;
	else if (keycode == 40 && p->l->ratio == 0)
		p->l->ratio = 1;
	return (0);
}

int	key_hook(int keycode, t_var *p)
{
	if (keycode == 53)
		closewin(p->data);
	if (keycode == 13)
		p->c->xyz.y += 5;
	if (keycode == 0)
		p->c->xyz.x -= 5;
	if (keycode == 1)
		p->c->xyz.y -= 5;
	if (keycode == 2)
		p->c->xyz.x += 5;
	if (keycode == 126)
		p->c->way.y += 0.05;
	if (keycode == 123)
		p->c->way.x -= 0.05;
	if (keycode == 125)
		p->c->way.y -= 0.05;
	if (keycode == 124)
		p->c->way.x += 0.05;
	if (keycode == 37 && p->a->ratio != 0)
		p->a->ratio = 0;
	else if (keycode == 37 && p->a->ratio == 0)
		p->a->ratio = 1;
	key_hook2(keycode, p);
	generator(p);
	return (0);
}

int	windowsop(t_var *p)
{
	t_data	data;

	p->data = &data;
	data.mlx = mlx_init();
	vardef(&data);
	data.win = mlx_new_window(data.mlx, data.winwidth, data.winlength, "UwU");
	data.img = mlx_new_image(data.mlx, data.winwidth, data.winlength);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	generator(p);
	mlx_hook(data.win, 17, 1L << 2, closewin, &data);
	mlx_key_hook(data.win, key_hook, p);
	mlx_loop(data.mlx);
	return (0);
}
