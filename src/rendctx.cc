#include "rendctx.h"
#include "scene.h"
#include "pixmap.h"

// defaults
RenderOptions::RenderOptions()
{
	width = 1280;
	height = 800;
	samples = 1;
	tmstart = tmend = 0;
	flags = ROPT_DEFAULT;

	blksize = 32;
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
	return false;
}

bool RenderContext::parse_args(int argc, char **argv)
{
	return false;
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
	scansize = 0;
	prio = 0;
}

FrameBlock::FrameBlock(int x, int y, int xsz, int ysz)
{
	this->x = x;
	this->y = y;
	width = xsz;
	height = ysz;
	scansize = prio = 0;
}
