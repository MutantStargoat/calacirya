#ifndef CALA_SURFACE_H_
#define CALA_SURFACE_H_

#include "xform_node.h"
#include "material.h"
#include "vmath/vector.h"
#include "vmath/ray.h"

class Surface;

struct SurfPoint {
	double t;
	Vector3 pos, normal, tangent;
	Vector2 tex;

	const Surface *surf;
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
