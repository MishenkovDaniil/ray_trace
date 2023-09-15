#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graphic_structures.h"
#include "bdrf_calc.h"
#include "ray_cast.h"
#include "screen.h"

static const double RADIUS = 100;

static const int COLOR_COMP_NUM = 4;
static const int ALPHA_COMP_IDX = 3;
static const int COLOR_MAX_VAL = 0xFF;
static const int LIGHT_NUM = 2;
static const Color BROWN = Color (128, 64, 48, 255);

static const int DELTA_CAN = 2;
static const int DELTA_LIGHT = 2;

int main ()
{
    sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    // sf::RenderTexture window_texture = sf::RenderTexture ();
    // window_texture.create (WINDOW_WIDTH, WINDOW_HEIGHT);

    Point cam_strt  (0, 0,0);
    Point light_start1 (-50, 0, 0);
    Point light_start2 (0, 150, 250);
    Sphere sphere (Point (0, 150, 0), RADIUS, Color (0xff, 0, 0, 0xff));

    // ray_cast ((Color *)screen, lights,LIGHT_NUM, sphere, cam_strt);
    
    // sf::Image ray_trace;
    // sf::Texture texture;
    // sf::Sprite sprite;

    // ray_trace.create (WINDOW_WIDTH, WINDOW_HEIGHT, screen);
    // texture.loadFromImage (ray_trace);
    // sprite.setTexture (texture);

    Button light_button (Point (0, 750), Point (50, 800), BROWN, "light", LIGHT);
    Button camera_button (Point (50, 750), Point (100, 800), BROWN, "camera", CAMERA);
    
    sf::Uint8 screen[COLOR_COMP_NUM * WINDOW_HEIGHT * WINDOW_WIDTH] = {0};
    assert (screen);
    
    Point lights[LIGHT_NUM] = {light_start1, light_start2};
    ray_cast ((Color *)screen, lights,LIGHT_NUM, sphere, cam_strt);
    
    sf::Image ray_cast_img;
    sf::Texture texture;
    sf::Sprite sprite;
    ray_cast_img.create (WINDOW_WIDTH, WINDOW_HEIGHT, screen);
        
    Button *buttons = new Button[2];
    buttons[0] = light_button;
    buttons[1] = camera_button;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && 
                     event.mouseButton.button == sf::Mouse::Left &&
                     (event.mouseButton.x || event.mouseButton.y))
            {
                double x = event.mouseButton.x;
                double y = event.mouseButton.y;
                if (light_button.contains (x, y))
                {
                    light_button.update (!(light_button.get_status ()));
                }
                else if (camera_button.contains (x, y))
                {
                    camera_button.update (!(camera_button.get_status ()));
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Left:
                    {
                        move_left (lights, &cam_strt, &light_button, 2); 
                        break;  
                    }
                    case sf::Keyboard::Right:
                    {
                        move_right (lights, &cam_strt, &light_button, 2);   
                        break;  
                    }
                    case sf::Keyboard::Up:
                    {
                        move_up (lights, &cam_strt, &light_button, 2);   
                        break;  
                    }
                    case sf::Keyboard::Down:
                    {
                        move_down (lights, &cam_strt, &light_button, 2);   
                        break;  
                    }
                    default:
                    {
                        break;
                    }
                }
                ray_cast ((Color *)screen, lights, LIGHT_NUM, sphere, cam_strt);
                ray_cast_img.create (WINDOW_WIDTH, WINDOW_HEIGHT, screen);
            }
        }
        
        texture.loadFromImage (ray_cast_img);
        sprite.setTexture (texture);

        window.clear();
        window.draw (sprite);

        light_button.draw (window, WINDOW_WIDTH, WINDOW_HEIGHT);
        camera_button.draw (window, WINDOW_WIDTH, WINDOW_HEIGHT);

        window.display();
    }
    
    // delete[] buttons;
    return 0;
}