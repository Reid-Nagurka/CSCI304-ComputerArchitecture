#ifndef OBJ_H
#define OBJ_H

#include "sphere.h"
#include "rt.h"
#include "vec.h"
#include "light.h"

//node
typedef struct NODE{
	SPHERE_T sph;
	COLOR_T color;
	struct NODE *next;
}OBJ_T;

void read_objs (OBJ_T **list);
COLOR_T trace (RAY_T ray, OBJ_T *list, LIGHT_T light);
int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal);
COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal);
#endif