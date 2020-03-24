#pragma once
#include <ostream>
#include <string>
#include "vendor.h"

class PowerLogger
{
public:
	enum class Level {
		INFO = 0,
		WARN = 1,
		ERRO = 2
	};

private:
	std::ostream* m_outStream;
	Level m_minLevel = Level::INFO;

	void logString(Level l, const std::string& message);

	PowerLogger();

public:

	static PowerLogger& get() {
		static PowerLogger l;
		return l;
	}

	static void setMinimumLevel(Level level);
	static void setOutStream(std::ostream& stream);

	template<typename ...Args> static void Log(Level l, const std::string& msg, Args&&...args) {
		get().logString(l, fmt::format(msg, args...));
	}

	template<typename ...Args> static void Error(const std::string& msg, Args&&...args) {
		Log(Level::ERRO, msg, args...);
	}

	template<typename ...Args> static void Warning(const std::string& msg, Args&&...args) {
		Log(Level::WARN, msg, args...);
	}

	template<typename ...Args> static void Info(const std::string& msg, Args&&...args) {
		Log(Level::INFO, msg, args...);
	}
};

using plog=PowerLogger;

template<typename ...Args> static void PLOG_INFO(const std::string& msg, Args&&...args) {
	PowerLogger::Info(msg, args...);
}

template<typename ...Args> static void PLOG_WARN(const std::string& msg, Args&&...args) {
	PowerLogger::Warning(msg, args...);
}

template<typename ...Args> static void PLOG_ERROR(const std::string& msg, Args&&...args) {
	PowerLogger::Error(msg, args...);
}