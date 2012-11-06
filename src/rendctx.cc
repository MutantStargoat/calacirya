#include "rendctx.h"
#include "scene.h"
#include "pixmap.h"

// defaults
RenderOptions::RenderOptions()
{
	width = 1280;
	height = 800;
	samples = 1;
	flags = ROPT_DEFAULT;
}

RenderContext::RenderContext()
{
	scn = 0;
	framebuf = 0;
}

RenderContext::~RenderContext()
{
	delete scn;
	delete framebuf;
}

bool load_config(const char *fname)
{
	return false;
}

bool parse_args(int argc, char **argv)
{
	return false;
}
