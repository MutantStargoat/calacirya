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
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <alloca.h>

#include "brdf.h"
#include "plugins.h"

using namespace calacirya;

static PluginSet<ReflectanceFunc> brdfs;

namespace calacirya {

ReflectanceFunc::~ReflectanceFunc()
{
}

double ReflectanceFunc::eval_energy(const SurfPoint &pt, const Vector3 &outdir, const Vector3 &indir) const
{
	Vector3 color = eval(pt, outdir, indir);

	// Using relative luminance.
	return 0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z;
}


#define HOME_BRDF_DIR	".calacirya/plugins/brdf"

void load_brdf_plugins()
{
	if(!brdfs.empty()) {
		fprintf(stderr, "BUG: don't call load_brdf_plugins twice!\n");
		return;
	}

	struct passwd *pw = getpwuid(getuid());
	char *path = (char*)alloca(strlen(pw->pw_dir) + strlen(HOME_BRDF_DIR) + 2);
	sprintf(path, "%s/%s", pw->pw_dir, HOME_BRDF_DIR);

	brdfs.add_search_path(path);
#ifdef PREFIX
	brdfs.add_search_path(PREFIX "/lib/calacirya/plugins/brdf");
#endif
	// TODO let the user specify additional paths in the rendering context options

	brdfs.load_plugins();
}

void unload_brdf_plugins()
{
	brdfs.empty();
}

ReflectanceFunc *get_brdf(const char *name)
{
	return brdfs[name];
}

} // namespace calacirya
