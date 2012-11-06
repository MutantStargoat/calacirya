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
#include "pixmap.h"
#include "imago/imago2.h"

Pixmap::Pixmap()
{
	width = height = 0;
	pixels = 0;
}

Pixmap::~Pixmap()
{
	release();
}

void Pixmap::release()
{
	if(pixels) {
		img_free_pixels(pixels);
	}

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

	release();

	pixels = pix;
	width = xsz;
	height = ysz;
	return true;
}

bool Pixmap::save(const char *fname) const
{
	if(!pixels) {
		return false;
	}

	return img_save_pixels(fname, pixels, width, height, IMG_FMT_RGBAF) == 0;
}
