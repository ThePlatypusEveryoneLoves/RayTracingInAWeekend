#ifndef HITTABLE_H
#define HITTABLE_H

#include "Vec3.h"
#include "Ray.h"

class hit_record {
  public:
    Point3 p;
    vec3 normal;
    double t;
};

class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif