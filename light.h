#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"
//#include "rt.h"
//#include "obj.h"

typedef struct {
	VEC_T loc;
} LIGHT_T;

//COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal);

#endif