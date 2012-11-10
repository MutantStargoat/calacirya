/*
Lambert BRDF plugin for calacirya
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
#include "brdf.h"
#include "material.h"
#include "vmath/vmath.h"

class LambertReflectanceFunc : public ReflectanceFunc {
public:
	virtual const char *get_name() const;
	virtual ReflectanceType get_type() const;
	virtual Vector3 eval(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const;
	virtual Vector3 sample_dir(const SurfPoint &pt, const Vector3 &outdir) const;
};

// this function is called by the BRDF plugin manager to create the BRDF
extern "C" ReflectanceFunc *create_brdf()
{
	return new LambertReflectanceFunc;
}

/* this function is called by the BRDF plugin manager when it no longer needs
 * this BRDF
 */
extern "C" void destroy_brdf(ReflectanceFunc *brdf)
{
	delete brdf;
}

const char *LambertReflectanceFunc::get_name() const
{
	return "lambert";
}

ReflectanceType LambertReflectanceFunc::get_type() const
{
	return ReflectanceType::diffuse;
}

Vector3 LambertReflectanceFunc::eval(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const
{
	// get the material of the surface
	const Material *mat = pt.surf->get_material();

	// evaluate the "diffuse" attribute
	Vector3 kd = mat->get_attrib("diffuse")(pt);

	// calculate lambert's cosine law and multiply by the diffuse color
	return kd * fabs(dot_product(pt.normal, indir));
}

Vector3 LambertReflectanceFunc::sample_dir(const SurfPoint &pt, const Vector3 &outdir) const
{
	// generate a random direction
	Vector3 dir = sphrand(1.0);

	// if it points the wrong way, flip it...
	if(dot_product(dir, pt.normal) < 0.0) {
		dir = -dir;
	}
	return dir;
}
