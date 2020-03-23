#include "jampch.h"
#include "PowerLogger.hpp"
#include <iostream>
#include <fmt/format.h>
#include <rlutil.h>

void PowerLogger::logString(Level l, const std::string& message)
{
    if (l < m_minLevel) return;

    std::ostream& str = *m_outStream;
    switch (l)
    {
    case Level::INFO:
        rlutil::setColor(rlutil::GREEN);
        str << ("[DEBUG] ");
        break;
    case  Level::WARN:
        rlutil::setColor(rlutil::YELLOW);
        str << ("[WARNING] ");
        break;
    case  Level::ERRO:
        rlutil::setColor(rlutil::RED);
        str << ("[ERROR] ");
        break;
    default:
        break;
    }

	rlutil::setColor(rlutil::WHITE);
    str << message << std::endl;
}

PowerLogger::PowerLogger()
{
    m_outStream = &std::cout;
}

void PowerLogger::setMinimumLevel(Level level)
{
    get().m_minLevel = level;
}

void PowerLogger::setOutStream(std::ostream& stream)
{
    get().m_outStream = &stream;
}


