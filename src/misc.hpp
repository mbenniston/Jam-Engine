#pragma once
#include "PowerLogger.hpp"

#ifndef NDEBUG
	#define MISC_CHECK_GEN_ID(id) if ((id) != 0) PLOG_WARN(std::string("Possible Double Gen! " __FILE__ ":") + std::to_string(__LINE__));
	#define MISC_CHECK_REM_ID(id) if ((id) == 0) PLOG_WARN(std::string("Possible Double Remove! " __FILE__ ":") + std::to_string(__LINE__));
#else
	#define MISC_CHECK_GEN_ID(id) 
	#define MISC_CHECK_REM_ID(id) 
#endif