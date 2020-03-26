#pragma once
#include "PowerLogger.hpp"
#include "LeakChecker.hpp"

static bool rectInRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    return ((x1 > x2 && x1 < x2 + w2) || (x1 + w1 > x2 && x1 + w1 < x2 + w2)) && ((y1 > y2 && y1 < y2 + h2) || (y1 + h1 > y2 && y1 + h1 < y2 + h2));
}

#ifndef NDEBUG
	#define MISC_CHECK_GEN_ID(id) if ((id) != 0) PLOG_WARN(std::string("Possible Double Gen! " __FILE__ ":") + std::to_string(__LINE__)); LeakChecker::inc();
	#define MISC_CHECK_REM_ID(id) if ((id) == 0) PLOG_WARN(std::string("Possible Double Remove! " __FILE__ ":") + std::to_string(__LINE__)); LeakChecker::dec();
	#define MISC_LINC() LeakChecker::inc()
	#define MISC_LDEC() LeakChecker::dec()
#else
	#define MISC_CHECK_GEN_ID(id) 
	#define MISC_CHECK_REM_ID(id) 
	#define MISC_LINC()
	#define MISC_LDEC() 
#endif