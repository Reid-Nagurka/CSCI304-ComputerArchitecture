#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "vec.h"

//VEC_T normalize (VEC_T v);
//double dot (VEC_T v1, VEC_T v2);

VEC_T normalize (VEC_T v)
{
	//VEC_T newvec;
	double x; double y; double z;
	x = v.x; y = v.y; z = v.z;
	
	double d = (x*x) + (y*y) + (z*z);
	d = sqrt(d);
	
	x /= d; y /= d; z /= d;
	//newvec.x = x; newvec.y = y; newvec.z = z;
	v.x = x; v.y = y; v.z = z;
	return v;
}

double dot (VEC_T v1, VEC_T v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
