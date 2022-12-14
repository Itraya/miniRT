/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:56:50 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/14 10:38:29 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

void	ft_increase(int m[3], char c)
{
	if (c == 'A')
		m[0]++;
	if (c == 'C')
		m[1]++;
	if (c == 'L')
		m[2]++;
}

void	ft_null(int m[3])
{
	m[0] = 0;
	m[1] = 0;
	m[2] = 0;
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '	'))
		i++;
	if ((s[i] && s[i] == '\n') || !s[i])
		return (0);
	return (1);
}

int	verif_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 2] == 'r' && str[i - 1] == 't')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_var	p;

	if (ac != 2 || !verif_end(av[1]) || !verif_input(av[1]))
	{
		ft_putstr_fd("input problem\n", 2);
		return (1);
	}
	if (!parse_struc(&p, av[1]))
	{
		ft_putstr_fd("problem in parsing\n", 2);
		return (1);
	}
	windowsop(&p);
	free_struc(&p);
}
