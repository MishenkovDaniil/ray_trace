#include <iostream>

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

        // bdrf_calc (bdrf, lights[0], screen_p, sphere, cam_strt);

        int light_idx = 1;
        bdrf_calc (bdrf, lights[0], screen_p, sphere, cam_strt);
        screen[pixel_num] = sphere.get_color () * bdrf.diffuse +  white * bdrf.spectacular;
        while (light_number--)
        {
            bdrf_calc (bdrf, lights[light_idx++], screen_p, sphere, cam_strt);
            screen[pixel_num] += sphere.get_color () * bdrf.diffuse +  white * bdrf.spectacular;
        }
    }    
}

void move_left (Point *lights, Point *cam_strt, Button *buttons, int button_num)
{
    int button_idx = 0;
    bool change = false;
    while (button_num)
    {
        if (buttons[button_idx].get_status ())
        {
            change = true;
            break;
        }
        button_idx++;
        button_num--;
    }

    if (buttons[button_idx].get_button_use () == LIGHT)
    {
        lights[0].x_ -= 2;
    }
    else if (buttons[button_idx].get_button_use () == CAMERA)
    {
        cam_strt->x_ -= 2;
    }
}

void move_right (Point *lights, Point *cam_strt, Button *buttons, int button_num)
{
    int button_idx = 0;
    bool change = false;
    while (button_num)
    {
        if (buttons[button_idx].get_status ())
        {
            change = true;
            break;
        }
        button_idx++;
        button_num--;
    }

    if (buttons[button_idx].get_button_use () == LIGHT)
    {
        lights[0].x_ += 2;
    }
    else if (buttons[button_idx].get_button_use () == CAMERA)
    {
        cam_strt->x_ += 2;
    }
}

void move_up (Point *lights, Point *cam_strt, Button *buttons, int button_num)
{
    int button_idx = 0;
    bool change = false;
    while (button_num)
    {
        if (buttons[button_idx].get_status ())
        {
            change = true;
            break;
        }
        button_idx++;
        button_num--;
    }

    if (buttons[button_idx].get_button_use () == LIGHT)
    {
        lights[0].y_ += 2;
    }
    else if (buttons[button_idx].get_button_use () == CAMERA)
    {
        cam_strt->y_ += 2;
    }
}

void move_down (Point *lights, Point *cam_strt, Button *buttons, int button_num)
{
    int button_idx = 0;
    bool change = false;
    while (button_num)
    {
        if (buttons[button_idx].get_status ())
        {
            change = true;
            break;
        }
        button_idx++;
        button_num--;
    }

    if (buttons[button_idx].get_button_use () == LIGHT)
    {
        lights[0].y_ -= 2;
    }
    else if (buttons[button_idx].get_button_use () == CAMERA)
    {
        cam_strt->y_ -= 2;
    }
}

//TODO
//make light_colour and make light class