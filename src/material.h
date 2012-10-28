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
#ifndef CALA_MATERIAL_H_
#define CALA_MATERIAL_H_

#include <string>
#include "vmath/vector.h"
#include "xform_node.h"
#include "texture.h"

class MatAttrib {
private:
	std::string name;
	Track3 value;
	const Texture *map;

public:
	inline MatAttrib();

	inline void set_value(float val, long tmsec = 0);
	inline void set_color(const Vector3 &col, long tmsec = 0);
	inline void set_texture(const Texture *tex);

	inline Vector3 operator ()(const Vector2 &tc = Vector2(0.0, 0.0)) const;
	inline Vector3 operator ()(const Vector3 &tc = Vector3(0.0, 0.0, 0.0)) const;
};

class Material {
public:
};

#endif	// CALA_MATERIAL_H_
