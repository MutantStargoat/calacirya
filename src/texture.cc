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
#include "texture.h"

using namespace calacirya;

static inline Vector3 tex_lookup(const Pixmap *pixmap, const Vector2 &tc);

Texture::~Texture()
{
}

Vector3 Texture::lookup(const Vector2 &texcoord) const
{
	return lookup(Vector3(texcoord.x, texcoord.y, 0.0));
}

// ---- Texture2D ----

Texture2D::Texture2D()
{
	img = 0;
}

Vector3 Texture2D::lookup(const Vector3 &texcoord) const
{
	return tex_lookup(img, (Vector2)texcoord);
}


// ---- Texture3D ----
Vector3 Texture3D::lookup(const Vector3 &texcoord) const
{
	if(slices.empty()) {
		return Vector3(0.0, 0.0, 0.0);
	}

	// locate slice (TODO: intra-slice filtering)
	int idx = (int)(texcoord.z * (float)slices.size()) % slices.size();
	return tex_lookup(slices[idx], (Vector2)texcoord);
}


// ---- TextureCube ----
TextureCube::TextureCube()
{
	for(int i=0; i<6; i++) {
		sides[i] = 0;
	}
}

Vector3 TextureCube::lookup(const Vector3 &texcoord) const
{
	/* find the dominant axis to select a cubemap side, then
	 * use the other two coordinates as 2D texture coords in that side
	 */
	float absx = fabs(texcoord.x);
	float absy = fabs(texcoord.y);
	float absz = fabs(texcoord.z);

	int side;
	Vector2 tc;

	if(absx > absy && absx > absz) {
		side = 0;
		tc.x = texcoord.y;
		tc.y = texcoord.z;
	} else if(absy > absx && absy > absz) {
		side = 1;
		tc.x = texcoord.x;
		tc.y = texcoord.z;
	} else {
		side = 2;
		tc.x = texcoord.x;
		tc.y = texcoord.y;
	}

	return tex_lookup(sides[side], tc);
}

static inline Vector3 tex_lookup(const Pixmap *pixmap, const Vector2 &tc)
{
	// TODO implement filtering and wrapping modes
	int x = (int)(tc.x * pixmap->width) % pixmap->width;
	int y = (int)(tc.y * pixmap->height) % pixmap->height;

	float *ptr = pixmap->pixels + (y * pixmap->width + x) * 4;

	return Vector3(ptr[0], ptr[1], ptr[2]);
}
