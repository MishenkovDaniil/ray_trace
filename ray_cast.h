#ifndef RAY_CAST_H
#define RAY_CAST_H


#include "bdrf_calc.h"
#include "ray_cast.h"
#include "graphic_structures.h"


void ray_cast   (Color *screen, const Point *lights, const int light_num, Sphere &sphere, const Point &cam_strt);
void move (Point *lights, Point *cam_strt, Button *buttons, const int button_num, sf::Keyboard::Key pressed_key);
void update_buttons (Button **buttons, const int button_num, double x, double y);

#endif /* RAY_CAST_H */