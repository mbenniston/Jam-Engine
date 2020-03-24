#include "jampch.h"
#include "LeakChecker.hpp"

#include "PowerLogger.hpp"

static unsigned long long counter = 0;

void LeakChecker::inc()
{
	counter++;
}

void LeakChecker::dec()
{
	counter--;
}

void LeakChecker::start()
{
	counter = 0;
}

void LeakChecker::stop()
{
	if (counter == 0) {
		PLOG_INFO("No resource leaks detected");
	}
	else {
		PLOG_WARN("{} resource leaks detected", counter);
	}
}

bool LeakChecker::hasLeaks()
{
	return counter != 0;
}
