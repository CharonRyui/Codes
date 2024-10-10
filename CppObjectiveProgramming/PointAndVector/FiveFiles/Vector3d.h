#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3d.h"

class Vector3d {
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Vector3d(double x, double y, double z);
    void print() const;
    friend Point3d;
};

#endif