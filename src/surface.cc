#include "surface.h"

Surface::Surface()
{
	material = 0;
}

Surface::~Surface()
{
}

void Surface::set_material(const Material *mat)
{
	material = mat;
}

const Material *Surface::get_material() const
{
	return material;
}
