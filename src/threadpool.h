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
#ifndef CALA_THREAD_POOL_H_
#define CALA_THREAD_POOL_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <list>

template <typename JobT>
class ThreadPool {
private:
	std::list<JobT> workq;
	std::mutex workq_mutex;
	std::condition_variable pending_cond;

	std::thread *threads;
	int num_threads;

	int work_left;

	bool quit;

	std::function<void(const JobT&)> work_func, done_func;

	void thread_func();
	int get_number_processors();

public:
	ThreadPool();
	ThreadPool(const std::function<void(const JobT&)> &workf);
	~ThreadPool();

	void set_work_func(const std::function<void(const JobT&)> &func);
	void set_done_func(const std::function<void(const JobT&)> &func);

	void start(int num_threads = 0);
	void stop();

	void add_work(const JobT &job);
	void clear_work();

	void wait_work() const;
	bool is_done() const;
};

#include "threadpool.tmpl"

#endif	/* CALA_THREAD_POOL_H_ */
