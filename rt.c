/* Reid Nagurka 3/15/2018 Section 02 (3:30-4:50)
Creates images of spheres using specified inputs.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "rt.h"
#include "obj.h"
#include "vec.h"
#include "light.h"

//void read_objs (OBJ_T **list);
//COLOR_T cast (RAY_T ray, OBJ_T *list);

int main()
{
	//print the ppm header info
	printf("P6\n1000 1000\n255\n");

	//list initially points to null
	OBJ_T *list = NULL;

	//color to print to ppm file
	COLOR_T color;
	//ray to test for intersection,
	RAY_T ray;
	//the origin will always be at (0,0,0)
	ray.or.x = 0; ray.or.y = 0; ray.or.z = 0;

	//t is needed for intersect_sphere
	double t;

	//loops
	int y; int x;

	//light source vector:
	LIGHT_T light;
	light.loc.x = 5; light.loc.y = 10; light.loc.z = 0;

	//read in info from file, need to pass address of list so it can be manipulated
	read_objs(&list);

	for(y = 0; y < 1000; y++)
	{
		for(x = 0; x < 1000; x++)
		{
			//make x and y x3d and y3d
			ray.dir.x = -.5 + x/1000.0;
			ray.dir.y = .5 - y/1000.0;
			ray.dir.z = 1;
			//normalize direction vector
			VEC_T vec;
			vec = normalize(ray.dir);
			ray.dir = vec;

			//light.loc = normalize(light.loc);

			color = trace(ray, list, light);

			//cap color
			if(color.R > 1.0)
				color.R = 1.0;
			if(color.G > 1.0)
				color.G = 1.0;
			if(color.B > 1.0)
				color.B = 1.0;

			printf("%c%c%c", (unsigned char) (color.R*255), (unsigned char) (color.G*255), (unsigned char) (color.B*255));


		}
	}


	//free memory
	OBJ_T *node;
	while(list != NULL)
	{
		node = list;
		list = list -> next;
		free(node);
	}

	return 0;
}

//reads spheres from stdin; creates linked list using dynamic memory
void read_objs (OBJ_T **list)
{
	double cx, cy, cz, rad, red, green, blue;
	OBJ_T *node;

	//*list = NULL;

	while(scanf("%lf %lf %lf %lf %lf %lf %lf", &cx, &cy, &cz, &rad, &red, &green, &blue) == 7)
	{
		node = (OBJ_T *) malloc(sizeof(OBJ_T));
		if(node == NULL)
		{
			printf("No more space.");
			return;
		}

		node -> sph.ctr.x = cx;
		node -> sph.ctr.y = cy;
		node -> sph.ctr.z = cz;
		node -> sph.r = rad;
		node -> color.R = red;
		node -> color.G = green;
		node -> color.B = blue;

		//link into list (we need to figure out how to put the new link into the list
		node -> next = *list;
		//set the header to point to the new link
		*list = node;
	}
}

//iterates through linked list; finds closest intersection using intersect_sphere; returns color of closest sphere
COLOR_T trace (RAY_T ray, OBJ_T *list, LIGHT_T light)
{
	double min_t = 10000;
	OBJ_T *curr;
	double t;
	COLOR_T color;
	//pointer for intersection point
	VEC_T int_pt;
	//pointer for N
	VEC_T normal;

	//initialize background to be black
	color.R = 0.0;
	color.G = 0.0;
	color.B = 0.0;

	//closest_surface_col, closest_int_pt and closest_norm are local variables to hold closest intersection point and closest normal
	COLOR_T closest_surface_col;
	VEC_T closest_int_pt;
	VEC_T closest_norm;

	for(curr = list; curr != NULL; curr = curr -> next)
	{
		if(intersect_sphere(ray, curr -> sph, &t, &int_pt, &normal))
		{
			if(t < min_t)
			{
				min_t = t;
				closest_surface_col = curr -> color;
				closest_int_pt = int_pt;
				closest_norm = normal;

				//not sure if all parameters are correct for illuminate.
				//color = illuminate(ray, light, list, closest_surface_col, closest_int_pt, closest_norm);

				//commented out below from old project
				//color = curr -> color;
				//min_t = t;
			}

			color = illuminate(ray, light, list, closest_surface_col, closest_int_pt, closest_norm);
		}

	}

	return color;
}
