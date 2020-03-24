#pragma once
#include "PowerLogger.hpp"
#include "LeakChecker.hpp"

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