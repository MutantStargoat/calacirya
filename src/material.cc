#include "material.h"

static MatAttrib default_attrib;

void Material::set_name(const char *name)
{
	this->name = name;
}

const char *Material::get_name() const
{
	return name.c_str();
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
