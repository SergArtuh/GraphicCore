#pragma once
#include "api.h"
#include "types.h"

#include <stdio.h>


#define LOG_ERROR(str, ...) common::Logger::Get().errorMsg( __LINE__, __FILE__, (str), __VA_ARGS__)
#define LOG_WARNING(str, ...) common::Logger::Get().warningMsg( __LINE__, __FILE__, (str), __VA_ARGS__)
#define LOG_INFO(str, ...) common::Logger::Get().infoMsg( __LINE__, __FILE__, (str), __VA_ARGS__)

namespace common {

	class COMMON_EXPORT ILoggerStrategy {
	public:
		virtual void Log(const char* const) = 0;
	};


	class COMMON_EXPORT DefaultLogStrategy : public ILoggerStrategy {
	public:
		virtual void Log(const char* const) override;
	};

	class COMMON_EXPORT Logger final {
	private:
		Logger();

		~Logger();
	public:
		static Logger & Get() {
			static Logger logger;
			return logger;
		}

		void SetStrategy(ILoggerStrategy*);

		void errorMsg(const int line, const char* const file, const const char* str, ...);

		void warningMsg(const int line, const char* const file, const char* str, ...);

		void infoMsg(const int line, const char* const file, const char* str, ...);
	private:
		void debugMsg(const int line, const char* const file, const char* str, const char* msgType, va_list args, bool isLogLocation = true);

		ILoggerStrategy* m_logStrategy = nullptr;;
	};
}