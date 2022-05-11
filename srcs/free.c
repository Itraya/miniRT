#include "../incl/miniRT.h"

void	free_struc(t_var *p)
{
	int	i;

	i = 0;
	while (i < 6)
		free(p->struc[i++]);
	free(p->struc);
}