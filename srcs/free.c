/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:53:29 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/04 13:04:15 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

void	free_struc(t_var *p)
{
	free(p->a);
	free(p->c);
	free(p->l);
	free(p->sp);
	free(p->pl);
	free(p->cy);
}

int	free_split(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
	return (0);
}
