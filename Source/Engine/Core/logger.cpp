#include "logger.h"
#include <iostream>
#include "FileIO.h"

namespace hop {

	bool Logger::log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel) {
		case LogLevel::Info:
			*m_ostream << "INFO: ";
			break;
		case LogLevel::Warning:
			*m_ostream << "WARNING: ";
			break;
		case LogLevel::Error:
			*m_ostream << "ERROR: ";
			break;
		case LogLevel::Assert:
			*m_ostream << "ASSERT: ";
			break;
		}
		*this << getFileName(filename) << "(" << line << ") ";
		return true;
	}
}