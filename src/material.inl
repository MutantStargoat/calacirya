MatAttrib::MatAttrib()
{
	map = 0;
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

Vector3 MatAttrib::operator ()(const Vector2 &tc) const
{
	if(tex) {
		return value * (Vector3)map->lookup(tc);
	}
	return value;
}

Vector3 MatAttrib::operator ()(const Vector3 &tc) const
{
	if(tex) {
		return value * (Vector3)map->lookup(tc);
	}
	return value;
}
