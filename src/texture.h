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
#ifndef CALA_TEXTURE_H_
#define CALA_TEXTURE_H_

#include <vector>
#include "vmath/vector.h"
#include "pixmap.h"

namespace calacirya {

// TODO add a plugin-based procedural texture subclass

class Texture {
public:
	virtual ~Texture();

	// TODO add some way to determine texel scale for filtering
	virtual Vector3 lookup(const Vector2 &texcoord) const;
	virtual Vector3 lookup(const Vector3 &texcoord) const = 0;
};

class Texture2D {
private:
	const Pixmap *img;

public:
	Texture2D();

	virtual Vector3 lookup(const Vector3 &texcoord) const;
};

class Texture3D {
private:
	std::vector<const Pixmap*> slices;

public:
	virtual Vector3 lookup(const Vector3 &texcoord) const;
};

class TextureCube {
private:
	const Pixmap *sides[6];

public:
	TextureCube();

	virtual Vector3 lookup(const Vector3 &texcoord) const;
};

}	// namespace calacirya

#endif	// CALA_TEXTURE_H_
