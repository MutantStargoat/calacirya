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
#include "rend.h"
#include "scene.h"
#include "camera.h"
#include "pixmap.h"

void render_frame(const RenderContext *ctx, long tmsec)
{

	// XXX: this is just a test version, later on it will break the
	// frame rendering into tasks and queue them to the worker pool
	for(int i=0; i<ctx->opt.height; i++) {
		render_scanline(ctx, i, tmsec);
	}
}

void render_scanline(const RenderContext *ctx, int scanline, long tmsec)
{
	const Scene *scn = ctx->scn;
	const Camera *cam = scn->get_active_camera();

	int xsz = ctx->opt.width;
	int ysz = ctx->opt.height;

	float *fbptr = ctx->framebuf->pixels + scanline * xsz * 3;

	for(int i=0; i<xsz; i++) {
		Vector3 color;

		for(int j=0; j<ctx->opt.samples; j++) {
			Ray ray = cam->get_primary_ray(i, scanline, xsz, ysz, j, tmsec);
			color += scn->trace_ray(ray);
		}

		color /= ctx->opt.samples;

		*fbptr++ = color.x;
		*fbptr++ = color.y;
		*fbptr++ = color.z;
	}
}
