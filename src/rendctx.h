#ifndef CALA_RENDCTX_H_
#define CALA_RENDCTX_H_

// global overrides to disable features if needed
enum {
	ROPT_MBLUR	= 1,	// motion blur
	ROPT_DOF	= 2		// depth of field
};
#define ROPT_DEFAULT	(ROPT_MBLUR | ROPT_DOF)

// TODO renderer selection
struct RenderOptions {
	int width, height;	// output image dimensions
	int samples;		// # samples per pixel

	unsigned int flags;	// bitmask, see above...

	RenderOptions();	// initialize defaults
};


class Scene;

class RenderContext {
public:
	RenderOptions opt;
	Scene *scn;

	RenderContext();
	~RenderContext();

	bool load_config(const char *fname);
	bool parse_args(int argc, char **argv);


};

#endif	// CALA_RENDCTX_H_
