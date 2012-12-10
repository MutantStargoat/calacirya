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
#include <string.h>
#include <new>
#include "pixmap.h"
#include "imago/imago2.h"

using namespace calacirya;

Pixmap::Pixmap()
{
	width = height = 0;
	pixels = 0;
}

Pixmap::~Pixmap()
{
	destroy();
}

Pixmap::Pixmap(const Pixmap &p)
{
	create(p.width, p.height, p.pixels);
}

Pixmap &Pixmap::operator =(const Pixmap &p)
{
	if(&p != this) {
		destroy();
	}
	create(p.width, p.height, p.pixels);
	return *this;
}

Pixmap::Pixmap(Pixmap &&p)
{
	width = p.width;
	height = p.height;
	pixels = p.pixels;

	p.pixels = 0;
}

Pixmap &Pixmap::operator =(Pixmap &&p)
{
	if(&p != this) {
		width = p.width;
		height = p.height;
		pixels = p.pixels;

		p.pixels = 0;
	}
	return *this;
}


bool Pixmap::create(int xsz, int ysz, float *pixels)
{
	try {
		this->pixels = new float[xsz * ysz * 3];
	}
	catch(std::bad_alloc &e) {
		return false;
	}

	if(pixels) {
		memcpy(this->pixels, pixels, xsz * ysz * 3 * sizeof *this->pixels);
	} else {
		memset(this->pixels, 0, xsz * ysz * 3 * sizeof *this->pixels);
	}

	width = xsz;
	height = ysz;
	return true;
}

void Pixmap::destroy()
{
	delete [] pixels;

	width = height = 0;
	pixels = 0;
}

bool Pixmap::load(const char *fname)
{
	int xsz, ysz;
	float *pix = (float*)img_load_pixels(fname, &xsz, &ysz, IMG_FMT_RGBAF);
	if(!pix) {
		return false;
	}

	destroy();
	create(xsz, ysz, pix);

	// we no longer need the pixel buffer returned by imago.
	img_free_pixels(pix);
	return true;
}

bool Pixmap::save(const char *fname) const
{
	if(!pixels) {
		return false;
	}

	return img_save_pixels(fname, pixels, width, height, IMG_FMT_RGBAF) == 0;
}
