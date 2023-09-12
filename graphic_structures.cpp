#include "graphic_structures.h"

void Point::update (double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

Vector Vector::operator * (const Vector &vec) const
{
    return Vector (y_ * vec.z_ - z_ * vec.y_, x_ * vec.z_ - z_ * vec.x_, x_ * vec.y_ - y_ * vec.x_);
}

Vector Vector::operator += (const Vector &vec)
{
    x_ += vec.x_;
    y_ += vec.y_;
    z_ += vec.z_;
    return *this;
}

Vector Vector::operator -= (const Vector &vec)
{
    x_ -= vec.x_;
    y_ -= vec.y_;
    z_ -= vec.z_;
    return *this;
}

Vector Vector::operator + (const Vector &vec) const
{
    return Vector (x_ + vec.x_, y_ + vec.y_, z_ + vec.z_);
}

Vector Vector::operator - (const Vector &vec) const
{
    return Vector (x_ - vec.x_, y_ - vec.y_, z_ - vec.z_);
}

Vector Vector::operator ! () const
{
    double module = sqrt (x_ * x_ + y_ * y_  + z_ * z_);

    return Vector (x_ / module, y_ / module, z_ / module);
}

Vector Vector::operator - () const
{
    return Vector (-x_, -y_, -z_);
}

Vector Vector::operator && (const double mult) const
{
    return Vector (x_ * mult, y_ * mult, z_ * mult);
}

double Vector::operator || (const Vector &vec) const 
{
    return x_ * vec.x_ + y_  * vec.y_ + z_ * vec.z_;
}

