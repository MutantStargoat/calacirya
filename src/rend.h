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
#ifndef CALA_REND_H_
#define CALA_REND_H_

namespace calacirya {

class RenderContext;
struct FrameBlock;

struct RenderJob {
	RenderContext *ctx;
	const FrameBlock *blk;
	long tmsec;
	int frame_number;
};

bool render_init(RenderContext *ctx);
void render_cleanup(RenderContext *ctx);

// registers a function to be called whenever a block has finished rendering
void render_done_func(RenderContext *ctx, void (*done_func)(const FrameBlock&));

void render_frame(RenderContext *ctx, long tmsec = 0);
void render_scanline(RenderContext *ctx, int scanline, long tmsec = 0);
void render_block(RenderContext *ctx, const FrameBlock &blk, long tmsec = 0);

}	// namespace calacirya

#endif	// CALA_REND_H_
