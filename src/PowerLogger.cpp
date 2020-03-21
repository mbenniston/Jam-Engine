#include "PowerLogger.hpp"
#include <fmt/format.h>
#include <rlutil.h>

void PowerLogger::Log(const std::string& msg)
{
	rlutil::setBackgroundColor(rlutil::YELLOW);
	fmt::print(msg);
}
