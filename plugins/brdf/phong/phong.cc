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
	// TODO get material attributes from pt.surf->get_material() and evaluate
	return Vector3(0, 0, 0);
}

Vector3 PhongReflectanceFunc::sample_dir(const SurfPoint &pt, const Vector3 &outdir) const
{
	// TODO randomly generate a sample ray direction
	return Vector3(0, 1, 0);
}
