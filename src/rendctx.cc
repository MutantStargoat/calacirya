#include "ncf/ncf1.h"
#include "ncf/util.h"
#include "rendctx.h"
#include "scene.h"
#include "pixmap.h"

using namespace calacirya;

// defaults
RenderOptions::RenderOptions()
{
	width = 1280;
	height = 800;
	samples = 1;
	tmstart = tmend = 0;
	flags = ROPT_DEFAULT;

	blksize = 32;
	num_threads = 0;	// auto-detect
}

void RenderOptions::enable(unsigned int bit)
{
	flags |= bit;
}

void RenderOptions::disable(unsigned int bit)
{
	flags &= ~bit;
}

bool RenderOptions::is_enabled(unsigned int bit)
{
	return (flags & bit) != 0;
}

RenderContext::RenderContext()
{
	scn = 0;
	framebuf = 0;
	blocks = 0;
	num_blocks = 0;
}

RenderContext::~RenderContext()
{
	delete scn;
	delete framebuf;
}

bool RenderContext::load_config(const char *fname)
{
	NCF::NCF1 config;

	config.source(fname);

	if (config.parse()) {
		return false;
	}

	/* Todo
	 * - Add the animation range options.
	*/

	int w = NCF::to_int(config.group("framebuffer")->get("width"));
	int h = NCF::to_int(config.group("framebuffer")->get("height"));
	int b = NCF::to_int(config.group("framebuffer")->get("block_size"));
	int s = NCF::to_int(config.group("antialiasing")->get("samples"));
	if (w > 0) opt.width = w;
	if (h > 0) opt.height = h;
	if (b > 0) opt.blksize = b;
	if (s > 0) opt.samples = s;

	// Rendering options
	int nthr = NCF::to_int(config.group("options")->get("threads"));
	if(nthr > 0) {
		opt.num_threads = nthr;
	}

	if (config.group("options")->query_property("motion_blur")) {
		bool flag = NCF::to_bool(config.group("options")->get("motion_blur"));

		if (flag)
			opt.enable(ROPT_MBLUR);
		else
			opt.disable(ROPT_MBLUR);
	}

	if (config.group("options")->query_property("depth_of_field")) {
		bool flag = NCF::to_bool(config.group("options")->get("depth_of_field"));

		if (flag)
			opt.enable(ROPT_DOF);
		else
			opt.disable(ROPT_DOF);
	}


	return false;
}

bool RenderContext::parse_args(int argc, char **argv)
{
	for(int i=1; i<argc; i++) {
		if(argv[i][0] == '-') {
			if(strcmp(argv[i], "-size") == 0) {
				int x, y;
				if(sscanf(argv[++i], "%dx%d", &x, &y) == 2) {
					opt.width = x;
					opt.height = y;
				} else {
					fprintf(stderr, "-size must be followed by <width>x<height>\n");
					return false;
				}

			} else if(strcmp(argv[i], "-threads") == 0) {
				char *endp;
				int thr = strtol(argv[++i], &endp, 10);
				if(endp != argv[i]) {
					opt.num_threads = thr;
				} else {
					fprintf(stderr, "-threads must be followed by the number of threads to use\n");
					return false;
				}
			} // TODO more...
		} else {
			if(!scn) {
				scn = new Scene;
			}
			if(!scn->load(argv[i])) {
				return false;
			}
		}
	}
	return true;
}

#define MIN(a, b)	((a < b) ? (a) : (b))

void RenderContext::set_block_size(int xsz, int ysz)
{
	int xcount = (opt.width + xsz - 1) / xsz;
	int ycount = (opt.height + ysz - 1) / ysz;
	num_blocks = xcount * ycount;

	delete [] blocks;
	blocks = new FrameBlock[num_blocks];
	FrameBlock *bptr = blocks;

	int y = 0;
	for(int i=0; i<ycount; i++) {
		int x = 0;

		for(int j=0; j<xcount; j++) {
			bptr->x = x;
			bptr->y = y;
			bptr->width = MIN(xsz, opt.width - x);
			bptr->height = MIN(ysz, opt.height - y);

			int dx = (j * 2 + 1) - xcount;
			int dy = (i * 2 + 1) - ycount;
			bptr->prio = (dx * dx + dy * dy) / 2;

			x += xsz;
			bptr++;
		}
		y += ysz;
	}
}

FrameBlock::FrameBlock()
{
	x = y = width = height = 0;
	prio = 0;
}

FrameBlock::FrameBlock(int x, int y, int xsz, int ysz)
{
	this->x = x;
	this->y = y;
	width = xsz;
	height = ysz;
	prio = 0;
}
