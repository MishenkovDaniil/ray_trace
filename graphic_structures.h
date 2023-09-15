#ifndef GRAPHIC_STRUCTURES_H
#define GRAPHIC_STRUCTURES_H

#include <cstring>
#include <cassert>
#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>


enum Buttons 
{
    NONE, 
    LIGHT, 
    CAMERA
};

class Color
{
public:
    uint8_t r_ = 0;
    uint8_t g_ = 0;
    uint8_t b_ = 0;
    uint8_t a_ = 0;

public:
    Color () {;};
    Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r_(r), g_ (g), b_ (b), a_(a) {};

    Color operator *  (double mult) const;
    Color operator +  (const Color &color) const;
    Color operator += (const Color &color);
    operator sf::Color() {return sf::Color (r_, g_, b_, a_);};
};

class Point 
{
public:

    double x_ = 0;
    double y_ = 0;
    double z_ = 0;

public:
    Point (double x, double y, double z) : x_ (x), y_ (y), z_ (z) {};
    Point (double x, double y) : x_ (x), y_ (y), z_ (0) {};
    Point (const Point &point) : x_ (point.x_), y_ (point.y_), z_ (point.z_) {};

    void update (double x, double y, double z);
};

class Button 
{
    Point lh_corner_ = Point (0, 0, 0); /// z coord is not used!!!
    Point rl_corner_ = Point (0, 0, 0); /// z coord is not used!!!
    bool is_pressed_ = false;
    Color color_ = Color ();
    char *string_ = nullptr;
    int str_size = 0;
    int button_use_ = NONE;
    Color pressed_button_color = Color (0, 0xff, 0, 0xff);
    Color unpressed_button_color = Color ();

public:
    Button () {;};
    Button (Point lh_corner, Point rl_corner, Color color, const char *string, const int button_use) :
                                                        lh_corner_ (lh_corner), 
                                                        rl_corner_ (rl_corner),
                                                        is_pressed_ (false),
                                                        color_ (color),
                                                        unpressed_button_color (color),
                                                        button_use_ (button_use)
                                                        {str_size = sizeof(string);
                                                         string_ = new char[str_size + 1];
                                                         assert (string_);
                                                         std::strcpy (string_, string); 
                                                        };
    ~Button () {delete[] string_;};

    void draw (sf::RenderWindow &window, int screen_h, int screen_w);
    void update (bool is_pressed);
    bool get_status () {return is_pressed_;};
    bool contains (double x, double y);
    int get_button_use () {return button_use_;};
};


class Vector 
{
public://
    double x_ = 0;
    double y_ = 0;
    double z_ = 0;

public:
    Vector (double x, double y, double z) : x_ (x), y_ (y), z_ (z) {};
    Vector (const Point &start, const Point &end) : x_ (end.x_ - start.x_),
                                                    y_ (end.y_ - start.y_), 
                                                    z_ (end.z_ - start.z_) {};
    Point vec_to_point () {return Point (x_, y_, z_);};

    Vector operator *  (const Vector &vec)const; //векторное произведение
    Vector operator +  (const Vector &vec)const;
    Vector operator += (const Vector &vec);
    Vector operator -= (const Vector &vec);
    Vector operator -  (const Vector &vec)const;
    Vector operator -  ()const;
    Vector operator && (const double mult)const;  // покоординатное умножение
    Vector operator !  () const;                  // нормализация вектора
    double operator || (const Vector &vec)const ; // скалярное умножение
};

class Sphere
{
    Point start_    = Point (0, 0, 0);
    double radius_  = 0;
    Color color_    = Color ();

public:
    Sphere (const Point& point, double r, Color sphere_color = Color (0, 0, 0, 0)) : start_ (point), radius_ (r), color_ (sphere_color){};
    Point  get_start  () {return start_ ;};
    double get_radius () {return radius_;};
    Color  get_color  () {return color_ ;};
};

class Observer 
{
public:
    Point start     = Point (0, 0, 0);
    Point lh_corner = Point (0, 0, 0);
    Point rl_corner = Point (0, 0, 0);

public:
    Observer (const Point& strt, const Point& lh, const Point& rl) : start (strt), lh_corner (lh), rl_corner (rl) {};
};

#endif /* GRAPHIC_STRUCTURES_H */