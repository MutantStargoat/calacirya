#ifndef CALA_SPHERE_H_
#define CALA_SPHERE_H_

#include "surface.h"

class Sphere : public Surface {
private:
	double radius;

public:
	Sphere();

	void set_radius(double rad);
	double get_radius() const;

	virtual bool intersect(const Ray &ray, SurfPoint *sp) const;
};

#endif	// CALA_SPHERE_H_
