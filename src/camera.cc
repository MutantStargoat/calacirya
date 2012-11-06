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
#include "camera.h"
#include "vmath/vmath.h"

static void calc_sample_pos_rec(int sidx, float xsz, float ysz, float *pos);


Camera::Camera()
{
	fov = M_PI / 4.0;
}

Vector2 Camera::calc_sample_pos(int x, int y, int xsz, int ysz, int sample) const
{
	float ppos[2];
	float aspect = (float)xsz / (float)ysz;

	float pwidth = 2.0 * aspect / (float)xsz;
	float pheight = 2.0 / (float)ysz;

	ppos[0] = (float)x * pwidth - aspect;
	ppos[1] = 1.0 - (float)y * pheight;

	calc_sample_pos_rec(sample, pwidth, pheight, ppos);
	return Vector2(ppos[0], ppos[1]);
}

Ray Camera::get_primary_ray(int x, int y, int xsz, int ysz, int sample, long tmsec) const
{
	Vector2 ppos = calc_sample_pos(x, y, xsz, ysz, sample);
	float z = 1.0 / tan(fov * 0.5);

	Ray ray(Vector3(0, 0, 0), Vector3(ppos.x, ppos.y, z));
	ray.time = tmsec;

	Matrix4x4 xform;
	get_xform(tmsec, &xform);

	return ray.transformed(xform);
}

/* generates a sample position for sample number sidx, in the unit square
 * by recursive subdivision and jittering
 */
static void calc_sample_pos_rec(int sidx, float xsz, float ysz, float *pos)
{
    static const float subpt[4][2] = {
        {-0.25, -0.25}, {0.25, -0.25}, {-0.25, 0.25}, {0.25, 0.25}
    };

    if(!sidx) {
        /* we're done, just add appropriate jitter */
        pos[0] += frand(xsz) - xsz / 2.0;
        pos[1] += frand(ysz) - ysz / 2.0;
        return;
    }

    /* determine which quadrant to recurse into */
    int quadrant = ((sidx - 1) % 4);
    pos[0] += subpt[quadrant][0] * xsz;
    pos[1] += subpt[quadrant][1] * ysz;

    calc_sample_pos_rec((sidx - 1) / 4, xsz / 2, ysz / 2, pos);
}

