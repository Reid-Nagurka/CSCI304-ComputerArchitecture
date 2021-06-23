#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "light.h"
#include "rt.h"
#include "obj.h"
#include "vec.h"

COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal)
{
    COLOR_T color;

    //L is vector from light location to intersection point
    VEC_T L;
    L.x = light.loc.x - int_pt.x;
    L.y = light.loc.y - int_pt.y;
    L.z = light.loc.z - int_pt.z;

    L = normalize(L);

    //AMBIENT
    color.R = 0.2 * surface_col.R;
    color.G = 0.2 * surface_col.G;
    color.B = 0.2 * surface_col.B;

    //DIFFUSE
    //Diffuse works for a single sphere
   double dotprod = dot(L, normal);
    //double dotprod = dot(L, N);

    if( dotprod > 0)
    {

        color.R += dotprod * surface_col.R;
        color.G += dotprod * surface_col.G;
        color.B += dotprod * surface_col.B;

        //SPECULOR
        VEC_T R;

        //try math with just doubles
        double nx; double ny; double nz;
        nx = normal.x * 2 * dotprod; ny = normal.y * 2 * dotprod; nz = normal.z * 2 * dotprod;

        R.x = L.x - nx;
        R.y = L.y - ny;
        R.z = L.z - nz;

        //normalize rad
        R = normalize(R);

        //V is ray direction
        double dotprodrv = dot(R, ray.dir);

        if(dotprodrv > 0)
        {
            color.R += pow(dotprodrv,200);
            color.G += pow(dotprodrv,200);
            color.B += pow(dotprodrv,200);
        }

    }

    return color;
}
