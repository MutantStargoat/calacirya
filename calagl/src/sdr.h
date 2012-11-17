#ifndef SDR_H_
#define SDR_H_

#include <vector>
#include "vmath/vmath.h"

class Shader {
private:
	bool compiled;

public:
	unsigned int sdr;

	Shader(unsigned int type);
	~Shader();

	void set_source(const char *src);

	bool compile();
	bool is_compiled() const;

	bool load(const char *fname);
};


// public shader manager interface
Shader *get_shader(const char *fname, unsigned int type);


class SdrProg {
private:
	// SdrProg does not own the shader objects
	std::vector<Shader*> shaders;
	bool linked;

public:
	unsigned int prog;

	SdrProg();
	~SdrProg();

	void add_shader(Shader *sdr);
	bool link();

	bool load(const char *vsfname, const char *psfname);

	int get_uniform_location(const char *name);
	int get_attribute_location(const char *name);

	void set_uniform(const char *name, int val);
	void set_uniform(const char *name, float val);
	void set_uniform(const char *name, const Vector2 &v);
	void set_uniform(const char *name, const Vector3 &v);
	void set_uniform(const char *name, const Vector4 &v);
	void set_uniform(const char *name, const Matrix4x4 &mat);

	void set_uniform(int loc, int val);
	void set_uniform(int loc, float val);
	void set_uniform(int loc, const Vector2 &v);
	void set_uniform(int loc, const Vector3 &v);
	void set_uniform(int loc, const Vector4 &v);
	void set_uniform(int loc, const Matrix4x4 &mat);
};

bool bind_program(const SdrProg *prog);

#endif	/* SDR_H_ */
