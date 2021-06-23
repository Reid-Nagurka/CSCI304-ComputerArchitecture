#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//#include "rt.h"
#include "sphere.h"
#include "obj.h"
//int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t);

//return 1 if intersection, 0 if not
int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal)
{
	//ray has or and dir. or and dir are vecs
	//sphere has ctr and r. ctr is a vec
	double B; double C;


	//everything should be normalized in main
	B = 2 * ((ray.dir.x * (ray.or.x - sphere.ctr.x)) +
			 (ray.dir.y * (ray.or.y - sphere.ctr.y)) +
			 (ray.dir.z * (ray.or.z - sphere.ctr.z)));


	double cvalx = ray.or.x - sphere.ctr.x;
	double cvaly = ray.or.y - sphere.ctr.y;
	double cvalz = ray.or.z - sphere.ctr.z;

	C = (cvalx * cvalx) + (cvaly * cvaly) + (cvalz * cvalz) - (sphere.r * sphere.r);

	//discriminant
	double dis = (B * B) - (4*C);
	//caveat 1:
	if(dis <= 0)
		return 0;

	//dis must be positive for the rest to run
	double t0; double t1;
	t0 = ( -B + sqrt(dis) ) / 2.0;
	t1 = ( -B - sqrt(dis) ) / 2.0;

	//caveat 2:
	if(t0 < 0 && t1 < 0)
		return 0;

	//we want the shorter positive value between t0 and t1

	//t0 is pos, t1 is neg
	if(t0 > 0 && t1 < 0)
		*t = t0;
	//t0 is neg, t1 is pos
	else if(t0 < 0 && t1 > 0)
		*t = t1;
	//t0 is pos, t1 is pos
	else if(t0 > 0 && t1 > 0)
	{
		//if t1 is the smaller val
		if(t0 > t1)
			*t = t1;
		//if t0 is the smaller val
		else if(t1 > t0)
			*t = t0;
		//if they're equal, just set to t0
		else
			*t = t0;
	}

	//added stuff for Final Project, not sure if this is where it should go.
	VEC_T temp;
	//temp = *int_pt;
	temp.x = ray.or.x + ray.dir.x * *t;
	temp.y = ray.or.y + ray.dir.y * *t;
	temp.z = ray.or.z + ray.dir.z * *t;
	*int_pt = temp;
	// int_pt -> x = ray.or.x + ray.dir.x * *t;
	// int_pt -> y = ray.or.y + ray.dir.y * *t;
	// int_pt -> z = ray.or.z + ray.dir.z * *t;

	VEC_T temp2;
	temp2.x = (int_pt -> x - sphere.ctr.x) / sphere.r;
	temp2.y = (int_pt -> y - sphere.ctr.y) / sphere.r;
	temp2.z = (int_pt -> z - sphere.ctr.z) / sphere.r;
	*normal = temp2;
	// normal -> x = (int_pt -> x - sphere.ctr.x) / sphere.r;
	// normal -> y = (int_pt -> y - sphere.ctr.y) / sphere.r;
	// normal -> z = (int_pt -> z - sphere.ctr.z) / sphere.r;


	return 1;
}
