#pragma once

namespace LeakChecker
{
	void inc();
	void dec();
	void start();
	void stop();
	bool hasLeaks();
}