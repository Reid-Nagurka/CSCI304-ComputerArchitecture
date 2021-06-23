#ifndef RT_H
#define RT_H

#include "vec.h"
//#include "obj.h"

//ray
typedef struct {
	VEC_T or;
	VEC_T dir;
}RAY_T;

//color
typedef struct {
	double R;
	double G;
	double B;
}COLOR_T;

//void read_objs (OBJ_T **list);
//COLOR_T cast (RAY_T ray, OBJ_T *list);

#endif
