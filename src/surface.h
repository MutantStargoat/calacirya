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
#ifndef CALA_SURFACE_H_
#define CALA_SURFACE_H_

#include "xform_node.h"
#include "vmath/vector.h"
#include "vmath/ray.h"

class Surface;
class Material;

struct SurfPoint {
	double t;
	Vector3 pos, normal, tangent;
	Vector2 tex;

	const Surface *surf;
	const Ray *incray;
};

class Surface : public XFormNode {
protected:
	const Material *material;

public:
	Surface();
	virtual ~Surface();

	void set_material(const Material *mat);
	const Material *get_material() const;

	virtual bool intersect(const Ray &ray, SurfPoint *sp) const = 0;
};


#endif	// CALA_SURFACE_H_
