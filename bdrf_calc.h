#ifndef BDRF_CALC_H
#define BDRF_CALC_H

#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graphic_structures.h"

class BDRF 
{
    public:
    double diffuse = 0;
    double spectacular = 0;  
};

void bdrf_calc (BDRF &bdrf, const Point &light, const Point &screen_p, Sphere &sphere, const Point &cam_strt);
Point find_intersection (Sphere &sphere, const Vector &direction, const Point &cam_strt);
static const double BDRF_COMPONENT = 0.25; ///component which prevents color overflow
static const int SHININESS_FACTOR = 32;    

#endif /* BDRF_CALC_H */