#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graphic_structures.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const double dx = (double)100 / (double)WINDOW_WIDTH;
const double dz = (double)100 / (double)WINDOW_HEIGHT;
const double RADIUS = 100;



double calc_diffise (const Point &light, const Point &screen_p, Sphere &sphere, const Point &cam_strt);
Point find_intersection (Sphere &sphere, const Vector &direction, const Point &cam_strt);

Point find_intersection (Sphere &sphere, const Vector &direction, const Point &cam_strt)
{
    Point P (0, 0, 0);
    
    Vector cam_to_sphere_center (cam_strt, sphere.get_start ()); // AO
    Vector cam_to_sphere_center_norm = !cam_to_sphere_center;
    // Vector obs = ! Vector (cam_strt, screen_p); //AB
    Vector AK = (!direction) && ((sqrt(cam_to_sphere_center || cam_to_sphere_center)) * ((!direction) || cam_to_sphere_center_norm));
    Vector OK = -cam_to_sphere_center + AK;
    
    if ((OK||OK) > (sphere.get_radius () * sphere.get_radius ())) 
    {
        P = Point (NAN, NAN, NAN);
        // printf ("gg");
        return P;
    }
    // printf ("AK_vec = %lf, %lf, %lf\n", AK.x_, AK.y_, AK.z_);
    // printf ("OK_vec = %lf, %lf, %lf\nmod  = %lf\n", OK.x_, OK.y_, OK.z_, sqrt (OK||OK));
    // printf ("direction = %lf, %lf, %lf\n", direction.x_, direction.y_, direction.z_);
    Vector directsqrt = (!direction) && (sqrt ((sphere.get_radius () * sphere.get_radius ()) - (OK || OK)));
// printf ("direct * sqrt = %lf, %lf, %lf, %\n", directsqrt.x_, directsqrt.y_, directsqrt.z_);
    Vector AP = AK - directsqrt;
    // printf ("AP_vec = %lf, %lf, %lf\n", AP.x_, AP.y_, AP.z_);
    Vector P_vec = AP + Vector (Point (0, 0, 0), cam_strt);
    // printf ("P_vec = %lf, %lf, %lf\n", OK.x_, OK.y_, OK.z_);
    // while (1) 
        // ;
    // printf ("P_vec = %lf, %lf, %lf\n", P_vec.x_, P_vec.y_, P_vec.z_);

    P = P_vec.vec_to_point ();


    return P;
}

double calc_diffise (const Point &light, const Point &screen_p, Sphere &sphere, const Point &cam_strt)
{
    Vector dir (cam_strt, sphere.get_start ()); // AO
    // double dir_modulo = dir || dir;
    Vector obs = ! Vector (cam_strt, screen_p); //AB
    
    Point P = find_intersection (sphere, obs, cam_strt);
    if (std::isnan (P.x_) || std::isnan (P.y_) || std::isnan (P.z_))
    {
        return -1;
    }
    // printf ("P = %lf, %lf, %lf\n", P.x_, P.y_, P.z_);
    
    // Vector dir_norm = !dir;
    // Vector AK = dir && (obs || dir);
    // Vector OK = AK - dir;
    // Vector AP = dir - dir_norm && (sqrt (sphere.get_radius () * sphere.get_radius () - (OK || OK) * (OK || OK)));
    // Vector P_vec = AP + Vector (Point (0, 0, 0), cam_strt);
    // Point P = P_vec.vec_to_point ();
    Vector AP  (cam_strt, P);
    Vector light_vec (light, P);
    Vector normal (sphere.get_start (), P);
    normal = !normal;
    light_vec = !light_vec;

    double diffuse = light_vec || normal;
    diffuse = diffuse > 0 ? diffuse : 0;
    // printf ("%lf\n", diffuse);
    Vector reflected =  -light_vec - normal && (2 * ((-light_vec) || normal));
    double spectacular = (-!AP) || (!reflected);
    spectacular = spectacular > 0 ? spectacular : 0;

    return diffuse;
}


int main ()
{
    sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), "lighting");
    
    sf::Uint8 screen[4 * WINDOW_HEIGHT * WINDOW_WIDTH] = {0};
    assert (screen);

    Point cam_strt  (0,0,0);
    Point light_start (-50, 100, 100);
    Sphere sphere (Point (0, 150, 0), RADIUS);


    int k = 0;
    for (int i = 0; i < 4 * WINDOW_HEIGHT * WINDOW_WIDTH; i += 4)
    {
        
        int pixel_num = i / 4;                                      //
        double x = -50.0 + (double)(pixel_num % WINDOW_WIDTH) * dx;  // convert into our camera system 
        double z = 50.0 - (double)(pixel_num / WINDOW_WIDTH) * dz;  //
        Point screen_p (x, 50, z);

        // camera[i + 1] = 128 * cosinus;
        double cosinus = calc_diffise (light_start, screen_p, sphere, cam_strt);
        // camera[i + 2] = 128 * cosinus;
        screen[i + 3] = 0xff * cosinus;
        // camera[i+1] = cosinus > 0 ? camera[i+1] : 0;
        // camera[i+2] = cosinus > 0 ? camera[i+2] : 0;
        screen[i+3] = cosinus > 0 ? screen[i+3] : 0;
        // screen[i+1] = screen[i+2] = screen[i+3] * 0.5;
        if (screen[i+3]) screen[i] = 0xff;
        if (cosinus > 0 && cosinus < 0.9)
            k++;

    }    

    printf ("%d\n", k);
    
    sf::Image raytrace;
    raytrace.create (WINDOW_WIDTH, WINDOW_HEIGHT, screen);

    sf::Texture texture;
    texture.loadFromImage (raytrace);
    sf::Sprite sprite;
    sprite.setTexture (texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();
        window.draw (sprite);
        window.display();
    }

    return 0;
}