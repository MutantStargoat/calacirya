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
#include <float.h>
#include "scene.h"
#include "brdf.h"
#include "material.h"

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
	for(auto lt : lights) {
		delete lt;
	}
	delete accel;
}

bool Scene::load(const char *fname)
{
	FILE *fp;

	if(!(fp = fopen(fname, "rb"))) {
		fprintf(stderr, "failed to load scene file: %s: %s\n", fname, strerror(errno));
		return false;
	}

	bool res = load(fp);
	if(!res) {
		fprintf(stderr, "failed to load scene file: %s\n", fname);
	}
	fclose(fp);
	return res;
}

bool Scene::load(FILE *fp)
{
	// TODO
	return false;
}

void Scene::set_background(const Vector3 &col)
{
	bgcolor = col;
}

void Scene::add_surface(const Surface *surf)
{
	if(surf) {
		surfaces.push_back(surf);
	}
}

void Scene::add_light(const Light *lt)
{
	if(lt) {
		lights.push_back(lt);
	}
}

void Scene::add_camera(const Camera *cam)
{
	if(!cam) {
		return;
	}
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
		return shade(pt);
	}
	return bgcolor;
}

Vector3 Scene::shade(const SurfPoint &pt) const
{
	long tm = pt.incray->time;
	Vector3 vdir = -pt.incray->dir.normalized();

	const Material *mtl = pt.surf->get_material();
	Vector3 color;

	for(int i=0; i<mtl->get_brdf_count(); i++) {
		const ReflectanceFunc *brdf = mtl->get_brdf(i);

		for(auto lt : lights) {
			Vector3 ldir = (lt->get_position(tm) - pt.pos).normalized();

			color += brdf->eval(pt, vdir, ldir) * lt->get_color(tm);
		}
	}

	return color;
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
		pt->incray = &ray;
	}
	return nearest.surf != 0;
}
