#include "../incl/miniRT.h"

double	contactpl(t_pl plane, t_ray ray, t_var *p)
{
	double	denom;
	double	t;

	denom = vecdot(plane.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(plane.xyz, ray.origin), plane.way) / denom;
	if (t < 0.000000001)
		return (0);
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
	p->data->no = plane.way;
	return (t);
}


