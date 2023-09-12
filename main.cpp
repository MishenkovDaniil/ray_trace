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

const char *WINDOW_NAME = "ray_trace";

int main ()
{
    sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    
    sf::Uint8 screen[COLOR_COMP_NUM * WINDOW_HEIGHT * WINDOW_WIDTH] = {0};
    assert (screen);

    Point cam_strt  (0,0,0);
    Point light_start (-50, 0, 0);
    Sphere sphere (Point (0, 150, 0), RADIUS);


    for (int i = 0; i < COLOR_COMP_NUM * WINDOW_HEIGHT * WINDOW_WIDTH; i += COLOR_COMP_NUM)
    {
        
        int pixel_num = i / COLOR_COMP_NUM;                            //
                                                                       //
        double x = X_START + (double)(pixel_num % WINDOW_WIDTH) * DX;  // convert pixel into our coordinates
        double z = Z_START + (double)(pixel_num / WINDOW_WIDTH) * DZ;  //

        Point screen_p (x, 50, z);

        double cosine = bdrf_calc (light_start, screen_p, sphere, cam_strt);

        screen[i + ALPHA_COMP_IDX] = COLOR_MAX_VAL * cosine;
        screen[i + ALPHA_COMP_IDX] = cosine > 0 ? screen[i + ALPHA_COMP_IDX] : 0;

        if (screen[i + ALPHA_COMP_IDX]) 
        {
            screen[i + 2] = screen[i + 1] = COLOR_MAX_VAL;
        }
    }    
    
    sf::Image ray_trace;
    ray_trace.create (WINDOW_WIDTH, WINDOW_HEIGHT, screen);

    sf::Texture texture;
    texture.loadFromImage (ray_trace);
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