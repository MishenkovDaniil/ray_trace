#ifndef RAY_CAST_H
#define RAY_CAST_H


#include "bdrf_calc.h"
#include "ray_cast.h"
#include "graphic_structures.h"

void ray_cast  (Color *screen, const Point *lights, const int light_num, Sphere &sphere, const Point &cam_strt);
void move_left  (Point *lights, Point *cam_strt, Button *buttons, int button_num);
void move_right (Point *lights, Point *cam_strt, Button *buttons, int button_num);
void move_up    (Point *lights, Point *cam_strt, Button *buttons, int button_num);
void move_down  (Point *lights, Point *cam_strt, Button *buttons, int button_num);

#endif /* RAY_CAST_H */