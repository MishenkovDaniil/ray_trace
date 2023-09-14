#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graphic_structures.h"
#include "bdrf_calc.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

const double X_START = -50;
const double Z_START = 50;

const double X_END = 50;
const double Z_END = -50;

const double DX = (X_END - X_START) / (double)WINDOW_WIDTH;
const double DZ = (Z_END - Z_START) / (double)WINDOW_HEIGHT;

const double RADIUS = 100;

const int COLOR_COMP_NUM = 4;
const int ALPHA_COMP_IDX = 3;
const int COLOR_MAX_VAL = 0xFF;
const int LIGHT_NUM = 2;

const char *WINDOW_NAME = "ray_cast";


void ray_cast (Color *screen, const Point *lights, const int light_num, Sphere &sphere, const Point &cam_strt);

int main ()
{
    sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    
    sf::Uint8 screen[COLOR_COMP_NUM * WINDOW_HEIGHT * WINDOW_WIDTH] = {0};
    assert (screen);

    Point cam_strt  (0,0,0);
    Point light_start2 (-50, 0, 0);
    Point light_start1 (0, 150, 250);
    Sphere sphere (Point (0, 150, 0), RADIUS, Color (0xff, 0, 0, 0xff));

    Point lights[LIGHT_NUM] = {light_start1, light_start2};

    ray_cast ((Color *)screen, lights,LIGHT_NUM, sphere, cam_strt);
    
    sf::Image ray_trace;
    sf::Texture texture;
    sf::Sprite sprite;

    ray_trace.create (WINDOW_WIDTH, WINDOW_HEIGHT, screen);
    texture.loadFromImage (ray_trace);
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
// несколько экранных кнопок которые управляют сценой (поворот, смещение ) 
//make array of colours instead uint8 and make a parameter: figure colour                +++
//color --> vector //vector is not uint8 () and is not intuitive to use vectors here

void ray_cast (Color *screen, const Point *lights, const int light_num, Sphere &sphere, const Point &cam_strt)
{
    BDRF bdrf;

    Color white (0xff, 0xff, 0xff, 0xff);

    for (int pixel_num = 0; pixel_num < WINDOW_HEIGHT * WINDOW_WIDTH; pixel_num++)
    {
        int light_number = light_num;
                                                                       //
        double x = X_START + (double)(pixel_num % WINDOW_WIDTH) * DX;  // convert pixel into our coordinates
        double z = Z_START + (double)(pixel_num / WINDOW_WIDTH) * DZ;  //

        Point screen_p (x, 50, z);

        double cosine = 0;
        
        bdrf_calc (bdrf, lights[0], screen_p, sphere, cam_strt);

        int light_idx = 0;
        while (light_number--)
        {
            bdrf_calc (bdrf, lights[light_idx++], screen_p, sphere, cam_strt);
            screen[pixel_num] += sphere.get_color () * bdrf.diffuse +  white * bdrf.spectacular;
        }
    }    
}