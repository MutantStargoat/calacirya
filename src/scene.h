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
#ifndef CALA_SCENE_H_
#define CALA_SCENE_H_

#include <vector>
#include "surface.h"
#include "camera.h"
#include "rayaccel.h"

// XXX the scene owns all objects

class Scene {
private:
	Vector3 bgcolor;

	std::vector<const Surface*> surfaces;
	std::vector<const Camera*> cameras;
	const Camera *active_cam;

	RayAccel *accel;

public:
	Scene();
	~Scene();

	void set_background(const Vector3 &col);

	void add_surface(const Surface *surf);
	void add_camera(const Camera *cam);

	const Camera *find_camera(const char *name) const;

	void set_active_camera(const Camera *cam);
	const Camera *get_active_camera() const;

	Vector3 trace_ray(const Ray &ray) const;
	Vector3 shade(const SurfPoint &pt) const;

	/* finds the first hit of a ray with our geometry
	 * hit point details are reutrned by pointer hit
	 */
	bool find_hit(const Ray &ray, SurfPoint *pt) const;
};

#endif	// CALA_SCENE_H_
