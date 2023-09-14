#ifndef GRAPHIC_STRUCTURES_H
#define GRAPHIC_STRUCTURES_H

#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>


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
};

class Point 
{
public:

    double x_ = 0;
    double y_ = 0;
    double z_ = 0;

    Point (double x, double y, double z) : x_ (x), y_ (y), z_ (z) {};
    Point (const Point &point) : x_ (point.x_), y_ (point.y_), z_ (point.z_) {};

    void update (double x, double y, double z);
};

class Vector 
{
public:
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
    Point get_start   () {return start_ ;};
    double get_radius () {return radius_;};
    Color get_color   () {return color_ ;};
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