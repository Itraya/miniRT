/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:56:50 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/07 14:19:13 by mlagrang         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_var	p;

	if (ac != 2)
		return (1);
	if (!verif_input(av[1]))
	{
		dprintf(2, "input problem\n");
		return (1);
	}
	if (!parse_struc(&p, av[1]))
	{
		dprintf(2, "problem in parsing\n");
		return (1);
	}
	windowsop(&p);
	free_struc(&p);
}
