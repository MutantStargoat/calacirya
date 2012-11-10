#include "material.h"

void Material::set_name(const char *name)
{
	this->name = name;
}

const char *Material::get_name() const
{
	return name.c_str();
}

MatAttrib &Material::operator [](const char *attrname)
{
	return attribs[std::string(attrname)];
}

const MatAttrib &Material::operator [](const char *attrname) const
{
	return ((Material*)this)->attribs[std::string(attrname)];
}
