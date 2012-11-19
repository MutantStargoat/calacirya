#include <stdio.h>
#include <assert.h>
#include <map>
#ifdef _MSC_VER
#include <memory.h>
#else
#include <alloca.h>
#endif
#include <GL/glew.h>
#include "sdr.h"

Shader::Shader(unsigned int type)
{
	sdr = glCreateShader(type);
	compiled = false;

	assert(glGetError() == GL_NO_ERROR);
}

Shader::~Shader()
{
	glDeleteShader(sdr);
}

void Shader::set_source(const char *src)
{
	glShaderSource(sdr, 1, &src, 0);
	compiled = false;

	assert(glGetError() == GL_NO_ERROR);
}

bool Shader::compile()
{
	if(compiled) {
		return true;
	}

	glCompileShader(sdr);

	int len;
	glGetShaderiv(sdr, GL_INFO_LOG_LENGTH, &len);
	if(len) {
		char *buf = (char*)alloca(len + 1);
		glGetShaderInfoLog(sdr, len, &len, buf);
		fprintf(stderr, "compiler: %s\n", buf);
	}

	int status;
	glGetShaderiv(sdr, GL_COMPILE_STATUS, &status);
	if(!status) {
		fprintf(stderr, "shader compilation failed\n");
		return false;
	}

	compiled = true;
	return true;
}

bool Shader::is_compiled() const
{
	return compiled;
}

bool Shader::load(const char *fname)
{
	FILE *fp;

	if(!(fp = fopen(fname, "rb"))) {
		fprintf(stderr, "failed to open shader file: %s\n", fname);
		return false;
	}

	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	rewind(fp);

	char *buf = new char[sz + 1];
	if((long)fread(buf, 1, sz, fp) < sz) {
		fprintf(stderr, "failed to read shader contents\n");
		fclose(fp);
		return false;
	}
	fclose(fp);

	set_source(buf);
	delete [] buf;

	return compile();
}

// ---- shader manager ----
static std::map<std::string, Shader*> sdrcache;

Shader *get_shader(const char *fname, unsigned int type)
{
	auto it = sdrcache.find(std::string(fname));
	if(it != sdrcache.end()) {
		return it->second;
	}

	Shader *sdr = new Shader(type);
	if(!sdr->load(fname)) {
		delete sdr;
		return 0;
	}
	sdrcache[fname] = sdr;
	return sdr;
}


// ---- class SdrProg ----

SdrProg::SdrProg()
{
	prog = glCreateProgram();
	linked = false;
	assert(glGetError() == GL_NO_ERROR);
}

SdrProg::~SdrProg()
{
	glDeleteProgram(prog);
}

void SdrProg::add_shader(Shader *sdr)
{
	if(sdr->compile()) {
		glAttachShader(prog, sdr->sdr);
		assert(glGetError() == GL_NO_ERROR);

		shaders.push_back(sdr);
		linked = false;
	}
}

bool SdrProg::link()
{
	if(linked) {
		return true;
	}

	glLinkProgram(prog);

	int len;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if(len) {
		char *buf = (char*)alloca(len + 1);
		glGetProgramInfoLog(prog, len, &len, buf);
		assert(glGetError() == GL_NO_ERROR);
		fprintf(stderr, "linker: %s\n", buf);
	}

	int status;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if(!status) {
		fprintf(stderr, "program linking failed\n");
		return false;
	}

	linked = true;
	return true;
}

bool SdrProg::load(const char *vsfname, const char *psfname)
{
	Shader *sdr;

	if(vsfname) {
		if(!(sdr = get_shader(vsfname, GL_VERTEX_SHADER))) {
			return false;
		}
		add_shader(sdr);
	}

	if(psfname) {
		if(!(sdr = get_shader(psfname, GL_FRAGMENT_SHADER))) {
			return false;
		}
		add_shader(sdr);
	}
	return link();
}

int SdrProg::get_uniform_location(const char *name)
{
	bind_program(this);
	return glGetUniformLocation(prog, name);
}

int SdrProg::get_attribute_location(const char *name)
{
	bind_program(this);
	return glGetAttribLocation(prog, name);
}

void SdrProg::set_uniform(const char *name, int val)
{
	set_uniform(get_uniform_location(name), val);
}

void SdrProg::set_uniform(const char *name, float val)
{
	set_uniform(get_uniform_location(name), val);
}

void SdrProg::set_uniform(const char *name, const Vector2 &v)
{
	set_uniform(get_uniform_location(name), v);
}

void SdrProg::set_uniform(const char *name, const Vector3 &v)
{
	set_uniform(get_uniform_location(name), v);
}

void SdrProg::set_uniform(const char *name, const Vector4 &v)
{
	set_uniform(get_uniform_location(name), v);
}

void SdrProg::set_uniform(const char *name, const Matrix4x4 &mat)
{
	set_uniform(get_uniform_location(name), mat);
}


void SdrProg::set_uniform(int loc, int val)
{
	if(loc >= 0) {
		bind_program(this);
		glUniform1i(loc, val);
	}
}

void SdrProg::set_uniform(int loc, float val)
{
	if(loc >= 0) {
		bind_program(this);
		glUniform1f(loc, val);
	}
}

void SdrProg::set_uniform(int loc, const Vector2 &v)
{
	if(loc >= 0) {
		bind_program(this);
		glUniform2f(loc, v.x, v.y);
	}
}

void SdrProg::set_uniform(int loc, const Vector3 &v)
{
	if(loc >= 0) {
		bind_program(this);
		glUniform3f(loc, v.x, v.y, v.z);
	}
}

void SdrProg::set_uniform(int loc, const Vector4 &v)
{
	if(loc >= 0) {
		bind_program(this);
		glUniform4f(loc, v.x, v.y, v.z, v.w);
	}
}

void SdrProg::set_uniform(int loc, const Matrix4x4 &mat)
{
	if(loc >= 0) {
		bind_program(this);
		// loading transpose matrix (3rd arg true)
#ifdef SINGLE_PRECISION_MATH
		glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)mat.m);
#else
		glUniformMatrix4dv(loc, 1, GL_TRUE, (double*)mat.m);
#endif
	}
}

bool bind_program(const SdrProg *prog)
{
	if(!prog) {
		glUseProgram(0);
		return true;
	}

	if(!((SdrProg*)prog)->link()) {
		return false;
	}
	glUseProgram(prog->prog);
	if(glGetError()) {
		return false;
	}
	return true;
}
