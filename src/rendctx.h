/*
Calacirya is a photorealistic 3D renderer.
Copyright (C) 2012 John Tsiombikas <nuclear@member.fsf.org>,
               and Nikos Papadopoulos <nikpapas@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CALA_RENDCTX_H_
#define CALA_RENDCTX_H_

#include <functional>
#include <atomic>
#include "threadpool.h"
#include "rend.h"

namespace calacirya {

// global overrides to disable features if needed
enum {
	ROPT_MBLUR	= 1,	// motion blur
	ROPT_DOF	= 2		// depth of field
};
#define ROPT_DEFAULT	(ROPT_MBLUR | ROPT_DOF)

struct RenderOptions {
	int width, height;		// output image dimensions
	int samples;			// # samples per pixel
	long tmstart, tmend;	// rendering time interval (animation range)

	unsigned int flags;		// bitmask, see above...

	int blksize;			// render block size
	int num_threads;		// how many threads to use (0 means auto-detect)

	RenderOptions();		// initialize defaults

	void enable(unsigned int bit);
	void disable(unsigned int bit);
	bool is_enabled(unsigned int bit);
};


class Scene;
class Pixmap;
struct FrameBlock;
struct RenderJob;

class RenderContext {
public:
	RenderOptions opt;
	Scene *scn;
	Pixmap *framebuf;

	FrameBlock *blocks;
	int num_blocks;
	std::function<void(const FrameBlock&)> block_done_func;

	ThreadPool<RenderJob> rend_workers;
	std::atomic<int> current_frame;

	RenderContext();
	~RenderContext();

	bool load_config(const char *fname);
	bool parse_args(int argc, char **argv);

	void set_block_size(int xsz, int ysz);
};

struct FrameBlock {
	int x, y, width, height;
	int prio;		// render priority

	FrameBlock();
	FrameBlock(int x, int y, int xsz, int ysz);
};

}	// namespace calacirya

#endif	// CALA_RENDCTX_H_
