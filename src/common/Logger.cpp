#include "Logger.h"
#include <stdarg.h>


#define MAX_BUFFER_SIZE 2048


namespace common {

	Logger::Logger() : m_logStrategy{ new DefaultLogStrategy } {
	}

	Logger::~Logger() {
		if (m_logStrategy) {
			delete m_logStrategy;
		}
	}

	Logger& Logger::Get() {
		static Logger logger;
		return logger;
	}

	void Logger::SetStrategy(ILoggerStrategy * strategy) {
		if (m_logStrategy) {
			delete m_logStrategy;
			m_logStrategy = strategy;
		}
	}

	void Logger::debugMsg(const int line, const char* const file, const char* str, const char * msgType, va_list args, bool isLogLocation) {
		std::vector<char> buffer(MAX_BUFFER_SIZE);

		if (isLogLocation) {
			snprintf(buffer.data(), buffer.size(), "[ %s ] at line: %d, file %s:\t", msgType, line, file);
		}
		else {
			snprintf(buffer.data(), buffer.size(), "[ %s ]\t", msgType);
		}
		

		const size_t shift = strlen(buffer.data());

		vsnprintf(buffer.data() + shift, MAX_BUFFER_SIZE, str, args);

		//OutputDebugString(buffer.data());
		//OutputDebugString("\n");
		m_logStrategy->Log(buffer.data());
	}

	void Logger::errorMsg(const int line, const char* const file, const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(line, file, str, "Error", args);
		va_end(args);
	}

	void Logger::warningMsg(const int line, const char* const file, const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(line, file, str, "Warning", args);
		va_end(args);
	}

	void Logger::infoMsg(const int line, const char* const file, const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(line, file, str, "Info", args, false);
		va_end(args);
	}


	void DefaultLogStrategy::Log(const char* const msg) {
		printf(msg);
		printf("\n");
	}
}