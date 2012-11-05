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
	const Scene *scn = ctx->scn;
	const Camera *cam = scn->get_active_camera();

	float *fbptr = ctx->framebuf->pixels;

	int xsz = ctx->opt.width;
	int ysz = ctx->opt.height;

	// XXX: this is just a test version, later on it will break the
	// frame rendering into tasks and queue them to the worker pool
	for(int i=0; i<ysz; i++) {
		for(int j=0; j<xsz; j++) {
			for(int k=0; k<ctx->opt.samples; k++) {
				Ray ray = cam->get_primary_ray(j, i, xsz, ysz, k, tmsec);
				Vector3 color = scn->trace_ray(ray);

				*fbptr++ = color.x;
				*fbptr++ = color.y;
				*fbptr++ = color.z;
			}
		}
	}
}
