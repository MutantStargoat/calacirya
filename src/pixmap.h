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
#ifndef CALA_PIXMAP_H_
#define CALA_PIXMAP_H_

class Pixmap {
public:
	int width, height;
	float *pixels;

	Pixmap();
	~Pixmap();

	// copy
	Pixmap(const Pixmap &p);
	Pixmap &operator =(const Pixmap &p);

	// move
	Pixmap(Pixmap &&p);
	Pixmap &operator =(Pixmap &&p);

	bool create(int xsz, int ysz, float *pixels = 0);
	void destroy();

	bool load(const char *fname);
	bool save(const char *fname) const;
};

#endif	/* CALA_PIXMAP_H_ */
