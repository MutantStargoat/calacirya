/*
Phong BRDF plugin for calacirya
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

class PhongReflectanceFunc : public ReflectanceFunc {
public:
	virtual const char *get_name() const;
	virtual unsigned int get_type() const;
	virtual Vector3 eval(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const;
	virtual Vector3 sample_dir(const SurfPoint &pt, const Vector3 &outdir) const;
};

// this function is called by the BRDF plugin manager to create the BRDF
extern "C" ReflectanceFunc *create_plugin()
{
	return new PhongReflectanceFunc;
}

/* this function is called by the BRDF plugin manager when it no longer needs
 * this BRDF
 */
extern "C" void destroy_plugin(ReflectanceFunc *brdf)
{
	delete brdf;
}

const char *PhongReflectanceFunc::get_name() const
{
	return "phong";
}

unsigned int PhongReflectanceFunc::get_type() const
{
	return BRDF_SPECULAR;
}

Vector3 PhongReflectanceFunc::eval(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const
{
	const Material *mat = pt.surf->get_material();

	Vector3 ks = mat->get_attrib("specular")(pt);
	double shin = mat->get_attrib("shininess")(pt).x;

	// light reflection vector
	Vector3 lref = indir.reflection(pt.normal);

	double dot = dot_product(lref, outdir);
	if(dot < 0.0) {
		return Vector3(0, 0, 0);
	}
	return ks * pow(dot, shin);
}

Vector3 PhongReflectanceFunc::sample_dir(const SurfPoint &pt, const Vector3 &outdir) const
{
	const Material *mtl = pt.surf->get_material();
	double shin = mtl->get_attrib("shininess")(pt).x;

	Matrix4x4 mat;
	Vector3 ldir = outdir.normalized();
	Vector3 ref = ldir.reflection(pt.normal);

	double ndotl = dot_product(ldir, pt.normal);

	if(1.0 - ndotl > 1e-6) {
		Vector3 ivec, kvec, jvec;

		// build orthonormal basis
		if(fabs(ndotl) < 1e-6) {
			kvec = -ldir;
			jvec = pt.normal;
			ivec = cross_product(jvec, kvec);
		} else {
			ivec = cross_product(ldir, ref);
			jvec = ref;
			kvec = cross_product(ref, ivec);
		}

		mat.set_column_vector(ivec, 0);
		mat.set_column_vector(jvec, 1);
		mat.set_column_vector(kvec, 2);
	}

	double rnd1 = frand(1.0);
	double rnd2 = frand(1.0);

	double phi = acos(pow(rnd1, 1.0 / (shin + 1)));
	double theta = 2.0 * M_PI * rnd2;

	Vector3 v;
	v.x = cos(theta) * sin(phi);
	v.y = cos(phi);
	v.z = sin(theta) * sin(phi);
	return v.transformed(mat);
}
