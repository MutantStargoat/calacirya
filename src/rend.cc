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
#include <algorithm>
#include "rend.h"
#include "scene.h"
#include "camera.h"
#include "pixmap.h"
#include "threadpool.h"
#include "rendctx.h"

using namespace calacirya;


static void render_worker(const RenderJob &job);
static void render_done(const RenderJob &job);

namespace calacirya {

bool render_init(RenderContext *ctx)
{
	ctx->rend_workers.set_work_func(render_worker);
	ctx->rend_workers.set_done_func(render_done);

	ctx->rend_workers.start(ctx->opt.num_threads);
	return true;
}

void render_cleanup(RenderContext *ctx)
{
	ctx->rend_workers.stop();
}

void render_done_func(RenderContext *ctx, void (*done_func)(const FrameBlock&))
{
	ctx->block_done_func = done_func;
}

void render_frame(RenderContext *ctx, long tmsec)
{
	std::sort(ctx->blocks, ctx->blocks + ctx->num_blocks,
			[](const FrameBlock &a, const FrameBlock &b) { return a.prio < b.prio; });

	int frmno = ++ctx->current_frame;

	// add all the blocks to the work queue
	for(int i=0; i<ctx->num_blocks; i++) {
		RenderJob job = {ctx, ctx->blocks + i, tmsec, frmno};
		ctx->rend_workers.add_work(job);
	}
}

void render_scanline(RenderContext *ctx, int scanline, long tmsec)
{
	FrameBlock bscanln(0, scanline, ctx->opt.width, 1);
	render_block(ctx, bscanln, tmsec);
}

void render_block(RenderContext *ctx, const FrameBlock &blk, long tmsec)
{
	const Scene *scn = ctx->scn;
	const Camera *cam = scn->get_active_camera();

	int xsz = ctx->opt.width;
	int ysz = ctx->opt.height;
	int slskip = (xsz - blk.width) * 3;

	float *fbptr = ctx->framebuf->pixels + (blk.y * xsz + blk.x) * 3;

	for(int i=0; i<blk.height; i++) {
		for(int j=0; j<blk.width; j++) {
			Vector3 color;

			// for each pixel, cast multiple rays and average them all together
			for(int k=0; k<ctx->opt.samples; k++) {
				Ray ray = cam->get_primary_ray(blk.x + j, blk.y + i, xsz, ysz, k, tmsec);
				color += scn->trace_ray(ray);
			}
			color /= (float)ctx->opt.samples;

			*fbptr++ = color.x;
			*fbptr++ = color.y;
			*fbptr++ = color.z;
		}
		fbptr += slskip;
	}
}

}	// namespace calacirya


static void render_worker(const RenderJob &job)
{
	int curr_frame = job.ctx->current_frame;
	if(job.frame_number < curr_frame) {
		return;	// skip jobs leftover from previous frames
	}

	render_block(job.ctx, *job.blk, job.tmsec);
}

static void render_done(const RenderJob &job)
{
	// call the user-supplied completion notification callback
	if(job.ctx->block_done_func) {
		job.ctx->block_done_func(*job.blk);
	}
}
