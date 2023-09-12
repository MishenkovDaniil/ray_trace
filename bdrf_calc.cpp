#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graphic_structures.h"
#include "bdrf_calc.h"

Point find_intersection (Sphere &sphere, const Vector &direction, const Point &cam_strt)
{
    Point joint_point (0, 0, 0); 

    Vector cam_to_sphere_center (cam_strt, sphere.get_start ()); 
    Vector cam_to_sphere_center_norm = !cam_to_sphere_center;

    Vector AK = (!direction) && ((sqrt(cam_to_sphere_center || cam_to_sphere_center)) * ((!direction) || cam_to_sphere_center_norm));
    Vector OK = -cam_to_sphere_center + AK;
    
    if ((OK||OK) > (sphere.get_radius () * sphere.get_radius ())) 
    {
        joint_point = Point (NAN, NAN, NAN);
        return joint_point;
    }

    Vector directsqrt = (!direction) && (sqrt ((sphere.get_radius () * sphere.get_radius ()) - (OK || OK)));
    Vector AP = AK - directsqrt;
    Vector joint_point_vec = AP + Vector (Point (0, 0, 0), cam_strt);
    
    joint_point = joint_point_vec.vec_to_point ();

    return joint_point;
}

double bdrf_calc (const Point &light, const Point &screen_p, Sphere &sphere, const Point &cam_strt)
{
    Vector observer = ! Vector (cam_strt, screen_p);
    
    Point joint_point = find_intersection (sphere, observer, cam_strt);

    if (std::isnan (joint_point.x_) ||
        std::isnan (joint_point.y_) || 
        std::isnan (joint_point.z_))
        return -1;

    Vector AP  (cam_strt, joint_point);
    Vector light_vec (joint_point, light);
    Vector normal (sphere.get_start (), joint_point);
    
    double diffuse = (!light_vec) || (!normal);
           diffuse = diffuse > 0 ? diffuse : 0;

    Vector reflected =  -(light_vec - (normal && (2 * ((!light_vec) || (!normal)))));
    
    double spectacular = (!-AP) || (!reflected);
           spectacular = spectacular > 0 ? spectacular : 0;
           spectacular = pow (spectacular, SHININESS_FACTOR);

    return (diffuse + spectacular)*BDRF_COMPONENT;
}