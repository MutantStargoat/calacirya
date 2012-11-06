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
#include "scene.h"
#include <float.h>

Scene::Scene()
{
	accel = 0;
	active_cam = 0;
}

Scene::~Scene()
{
	for(auto s : surfaces) {
		delete s;
	}
	for(auto c : cameras) {
		delete c;
	}
	delete accel;
}

void Scene::set_background(const Vector3 &col)
{
	bgcolor = col;
}

void Scene::add_surface(const Surface *surf)
{
	surfaces.push_back(surf);
}

void Scene::add_camera(const Camera *cam)
{
	cameras.push_back(cam);
	if(!active_cam) {
		set_active_camera(cam);
	}
}

const Camera *Scene::find_camera(const char *name) const
{
	for(auto c : cameras) {
		if(strcmp(c->get_name(), name) == 0) {
			return c;
		}
	}
	return 0;
}

void Scene::set_active_camera(const Camera *cam)
{
	active_cam = cam;
}

const Camera *Scene::get_active_camera() const
{
	return active_cam;
}

Vector3 Scene::trace_ray(const Ray &ray) const
{
	SurfPoint pt;
	if(find_hit(ray, &pt)) {
		return shade(ray, pt);
	}
	return bgcolor;
}

Vector3 Scene::shade(const Ray &ray, const SurfPoint &pt) const
{
	return Vector3(1.0, 0.0, 0.0);	// TODO
}

bool Scene::find_hit(const Ray &ray, SurfPoint *pt) const
{
	if(accel) {
		return accel->find_hit(ray, pt);
	}

	// fallback to brute-force search
	SurfPoint nearest, tmp;
	nearest.t = DBL_MAX;
	nearest.surf = 0;

	for(auto s : surfaces) {
		if(s->intersect(ray, &tmp) && tmp.t < nearest.t) {
			nearest = tmp;
		}
	}

	if(pt) {
		*pt = nearest;
	}
	return nearest.surf != 0;
}
