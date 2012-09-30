#include "sphere.h"
#include "vmath/vmath.h"

Sphere::Sphere()
{
	radius = 1.0;
}

void Sphere::set_radius(double rad)
{
	radius = rad;
}

double Sphere::get_radius() const
{
	return radius;
}

bool Sphere::intersect(const Ray &ray, SurfPoint *sp) const
{
	Matrix4x4 xform, inv_xform;
	get_xform(ray.time, &xform, &inv_xform);

	// bring the ray to local space
	Ray local_ray = ray;
	local_ray.transform(inv_xform);

	double a = dot_product(ray.dir, ray.dir);
	double b = 2.0 * dot_product(ray.dir, ray.origin);
	double c = dot_product(ray.origin, ray.origin) - radius * radius;

	double discr = b * b - 4.0 * a * c;
	if(discr < 0.0)
		return false;

	double sqrt_discr = sqrt(discr);
	double t0 = (-b + sqrt_discr) / (2.0 * a);
	double t1 = (-b - sqrt_discr) / (2.0 * a);

	if(t0 < ERROR_MARGIN)
		t0 = t1;
	if(t1 < ERROR_MARGIN)
		t1 = t0;

	double t = t0 < t1 ? t0 : t1;
	if(t < ERROR_MARGIN)
		return false;

	// fill the SurfPoint structure
	sp->surf = this;
	sp->t = t;
	sp->pos = ray.origin + ray.dir * t;
	sp->normal = sp->pos / radius;
	sp->tangent = cross_product(Vector3(0, 1, 0), sp->normal);

	// spherically parametrize surface to derive texture coordinates
	double theta = atan2(sp->pos.z, sp->pos.x);
	double phi = acos(sp->pos.y / radius);
	sp->tex.x = theta / (2.0 * M_PI);
	sp->tex.y = phi / M_PI;
	return true;
}
