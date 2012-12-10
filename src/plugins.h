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
#ifndef CALA_PLUGINS_H_
#define CALA_PLUGINS_H_

#include <string>
#include <vector>
#include <map>

namespace calacirya {

template <typename T>
class Plugin {
private:
	std::string name;
	void *so;	// shared lib handle
	T *object;

public:
	Plugin();
	~Plugin();

	Plugin(const Plugin &p) = delete;
	Plugin &operator =(const Plugin &p) = delete;

	Plugin(Plugin &&p);
	Plugin &operator =(Plugin &&p);

	bool load(const char *fname);

	const char *get_name() const;

	T *get_object();
	const T *get_object() const;
};

template <typename T>
class PluginSet {
private:
	std::vector<std::string> paths;
	std::map<std::string, Plugin<T>> plugins;

	bool load_plugins_from(const char *path);

public:
	void add_search_path(const char *path);

	void load_plugins();
	void unload_plugins();

	T *operator [](const char *name);
	const T *operator [](const char *name) const;

	bool empty() const;
};

}	// namespace calacirya

#include "plugins.tmpl"

#endif	// CALA_PLUGINS_H_
