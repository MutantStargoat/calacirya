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
