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

namespace calacirya {

MatAttrib::MatAttrib()
{
	map = 0;
}

MatAttrib::MatAttrib(float val, long tmsec)
{
	map = 0;
	value.set_value(val, tmsec);
}

MatAttrib::MatAttrib(const Vector3 &col, long tmsec)
{
	map = 0;
	value.set_value(col, tmsec);
}

void MatAttrib::set_value(float val, long tmsec)
{
	value.set_value(Vector3(val, val, val), tmsec);
}

void MatAttrib::set_color(const Vector3 &col, long tmsec)
{
	value.set_value(col, tmsec);
}

void MatAttrib::set_texture(const Texture *tex)
{
	map = tex;
}

Vector3 MatAttrib::operator ()() const
{
	return (*this)(0, Vector3(0, 0, 0));
}

Vector3 MatAttrib::operator ()(const SurfPoint &pt) const
{
	return (*this)(pt.incray->time, pt.tex);
}

Vector3 MatAttrib::operator ()(long tm, const Vector3 &tc) const
{
	if(map) {
		return value(tm) * (Vector3)map->lookup(tc);
	}
	return value(tm);
}

}	// namespace calacirya
