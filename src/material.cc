
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
#include "material.h"

using namespace calacirya;

static MatAttrib default_attrib;

void Material::set_name(const char *name)
{
	this->name = name;
}

const char *Material::get_name() const
{
	return name.c_str();
}

void Material::add_brdf(const ReflectanceFunc *brdf)
{
	if(brdf) {
		reflist.push_back(brdf);
	}
}

const ReflectanceFunc *Material::get_brdf(int idx) const
{
	if(idx < 0 || idx >= (int)reflist.size()) {
		return 0;
	}
	return reflist[idx];
}

int Material::get_brdf_count() const
{
	return (int)reflist.size();
}

void Material::set_attrib(const char *name, const MatAttrib &mattr)
{
	attribs[std::string(name)] = mattr;
}

const MatAttrib &Material::get_attrib(const char *name) const
{
	auto it = attribs.find(std::string(name));
	if(it == attribs.end()) {
		return default_attrib;
	}
	return it->second;
}

MatAttrib &Material::operator [](const char *attrname)
{
	return attribs[std::string(attrname)];
}

const MatAttrib &Material::operator [](const char *attrname) const
{
	return get_attrib(attrname);
}
