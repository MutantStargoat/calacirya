/*
Calacirya is a photorealistic 3D renderer.
Copyright (C) 2012 John Tsiombikas <nuclear@member.fsf.org>,
               and Nikos Papadopoulos <nikpapas@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "sphere.h"
#include "vmath/vmath.h"

using namespace calacirya;

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

bool Sphere::intersect(const Ray &wray, SurfPoint *sp) const
{
	Matrix4x4 xform, inv_xform;
	get_xform(wray.time, &xform, &inv_xform);

	// bring the ray to local space
	Ray ray = wray.transformed(inv_xform);

	double a = dot_product(ray.dir, ray.dir);
	double b = 2.0 * dot_product(ray.dir, ray.origin);
	double c = dot_product(ray.origin, ray.origin) - radius * radius;

	double discr = b * b - 4.0 * a * c;
	if(discr < 0.0) {
		return false;
	}

	double sqrt_discr = sqrt(discr);
	double t0 = (-b + sqrt_discr) / (2.0 * a);
	double t1 = (-b - sqrt_discr) / (2.0 * a);

	if(t0 < ERROR_MARGIN) {
		t0 = t1;
	}
	if(t1 < ERROR_MARGIN) {
		t1 = t0;
	}

	double t = t0 < t1 ? t0 : t1;
	if(t < ERROR_MARGIN) {
		return false;
	}


	// fill the SurfPoint structure
	if(sp) {
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

		// bring everything back into world coordinates
		sp->pos.transform(xform);

		// inverse-transpose matrix needed for transforming normals
		Matrix4x4 invtrans_xform = inv_xform.transposed();
		sp->normal.transform(invtrans_xform);
		sp->tangent.transform(invtrans_xform);
	}
	return true;
}
