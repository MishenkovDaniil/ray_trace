#include <iostream>
#include <cassert>

#include "bdrf_calc.h"
#include "ray_cast.h"
#include "graphic_structures.h"
#include "screen.h"

// несколько экранных кнопок которые управляют сценой (поворот, смещение ) 
//make array of colours instead uint8 and make a parameter: figure colour                +++
//color --> vector //vector is not uint8 () and is not intuitive to use vectors here

void ray_cast (Color *screen, const Point *lights, const int light_num, Sphere &sphere, const Point &cam_strt)
{
    BDRF bdrf;

    Color white (0xff, 0xff, 0xff, 0xff);

    for (int pixel_num = 0; pixel_num < WINDOW_HEIGHT * WINDOW_WIDTH; pixel_num++)
    {
        int light_number = light_num - 1;
                                                                       //
        double x = X_START + (double)(pixel_num % WINDOW_WIDTH) * DX;  // convert pixel into our coordinates
        double z = Z_START + (double)(pixel_num / WINDOW_WIDTH) * DZ;  //

        Point screen_p (x, SCREEN_Y, z);

        bdrf_calc (bdrf, lights[0], screen_p, sphere, cam_strt);
        screen[pixel_num] = sphere.get_color () * bdrf.diffuse +  white * bdrf.spectacular;

        int light_idx = 1;
        while (light_number--)
        {
            bdrf_calc (bdrf, lights[light_idx++], screen_p, sphere, cam_strt);
            screen[pixel_num] += sphere.get_color () * bdrf.diffuse +  white * bdrf.spectacular;
        }
    }    
}


void move (Point *lights, Point *cam_strt, Button *buttons, const int button_num, sf::Keyboard::Key pressed_key)
{
    assert (lights &&  cam_strt && buttons);

    int button_idx = 0;
    bool change = false;
    int buttons_num = button_num;
    while (buttons_num)
    {
        if (buttons[button_idx].get_status ())
        {
            change = true;
            break;
        }
        button_idx++;
        buttons_num--;
    }


    switch (pressed_key)
    {
        case sf::Keyboard::Left:
        {
            if (buttons[button_idx].get_button_use () == LIGHT)
            {
                lights[0].x_ -= 2;
            }
            else if (buttons[button_idx].get_button_use () == CAMERA)
            {
                cam_strt->x_ -= 2;
            }
            break;  
        }
        case sf::Keyboard::Right:
        {
            if (buttons[button_idx].get_button_use () == LIGHT)
            {
                lights[0].x_ += 2;
            }
            else if (buttons[button_idx].get_button_use () == CAMERA)
            {
                cam_strt->x_ += 2;
            }
            break;  
        }
        case sf::Keyboard::Up:
        {
            if (buttons[button_idx].get_button_use () == LIGHT)
            {
                lights[0].y_ += 2;
            }
            else if (buttons[button_idx].get_button_use () == CAMERA)
            {
                cam_strt->y_ += 2;
            }
            break;  
        }
        case sf::Keyboard::Down:
        {
            if (buttons[button_idx].get_button_use () == LIGHT)
            {
                lights[0].y_ -= 2;
            }
            else if (buttons[button_idx].get_button_use () == CAMERA)
            {
                cam_strt->y_ -= 2;
            }
            break;  
        }
        default:
        {
            break;
        }
    }
}


void update_buttons (Button **buttons, const int button_num, double x, double y)
{
    int size_of_buttons = button_num;
    int button_idx = 0;

    while (size_of_buttons--)
    {
        if ((buttons[button_idx])->contains (x, y))
        {
            (buttons[button_idx])->update (!((buttons[button_idx])->get_status ()));
            break;
        }
        button_idx++;
    }
}

//TODO
//make light_colour and make light class