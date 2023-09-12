#ifndef GRAPHIC_STRUCTURES_H
#define GRAPHIC_STRUCTURES_H

#include <iostream>
#include <cmath>
#include <cassert>
#include <SFML/Graphics.hpp>

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

    Vector operator * (const Vector &vec)const; //векторное произведение
    Vector operator + (const Vector &vec)const;
    Vector operator += (const Vector &vec);
    Vector operator -= (const Vector &vec);
    Vector operator - (const Vector &vec)const;
    Vector operator - ()const;
    Vector operator && (const double mult)const; // покоординатное умножение
    Vector operator ! () const;                   // нормализация вектора
    double operator || (const Vector &vec)const ; // скалярное умножение
};

class Sphere
{
    Point start  = Point (0, 0, 0);
    double radius = 0;

public:
    Sphere (const Point& point, double r) : start (point), radius (r) {};
    Point get_start () {return start;};
    double get_radius () {return radius;};
};

class Observer 
{
public:
    Point start = Point (0, 0, 0);
    Point lh_corner = Point (0, 0, 0);
    Point rl_corner = Point (0, 0, 0);

public:
    Observer (const Point& strt, const Point& lh, const Point& rl) : start (strt), lh_corner (lh), rl_corner (rl) {};
};

#endif /* GRAPHIC_STRUCTURES_H */