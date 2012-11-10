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
#ifndef CALA_BRDF_H_
#define CALA_BRDF_H_

#include "surface.h"
#include "vmath/vector.h"

enum class ReflectanceType : unsigned int {
	diffuse = 1,
	specular = 2
};

/* ReflectanceFunc is the abstract base class representing a BRDF
 * (Bidirectional Reflectance Distribution Function).
 * All reflectance shader modules derive and implement this ADT interface.
 */
class ReflectanceFunc {
public:
	virtual ~ReflectanceFunc();

	virtual const char *get_name() const = 0;
	virtual ReflectanceType get_type() const = 0;

	/* evaluate the radiant exitance along "outdir", of light coming from "indir"
	 * returns the intensity for each color channel
	 */
	virtual Vector3 eval(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const = 0;

	/* evaluate the percentage of incident energy arriving from indir, which
	 * ends up reflecting towards outdir (this is just the mean of eval()'s RGB
	 * values).
	 */
	virtual double eval_energy(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const;

	// generate a random BRDF sampling direction
	virtual Vector3 sample_dir(const SurfPoint &pt, const Vector3 &outdir) const = 0;
};

#endif	// CALA_BRDF_H_
