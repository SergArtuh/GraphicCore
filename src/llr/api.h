#pragma once

#include <stdio.h>

#define LLR_EXPORT __declspec(dllexport)

#define LLR_ERROR(str, ...) llr::Logger::Get().errorMsg( __LINE__, __FILE__, (str), __VA_ARGS__)
#define LLR_WARNING(str, ...) llr::Logger::Get().warningMsg( __LINE__, __FILE__, (str), __VA_ARGS__)
#define LLR_INFO(str, ...) llr::Logger::Get().infoMsg( __LINE__, __FILE__, (str), __VA_ARGS__)

#define GL_CHECK { GLenum err = glGetError(); if(err != GL_NO_ERROR) {LLR_ERROR("OpenGL error with error code %x, at %d line %s", err, __LINE__, __FILE__);}}

#define UNUSED -1

namespace llr {

	class LLR_EXPORT ILoggerStrategy {
	public:
		virtual void Log(const char* const) = 0;
	};


	class LLR_EXPORT DefaultLogStrategy : public ILoggerStrategy {
	public:
		virtual void Log(const char* const) override;
	};

	class LLR_EXPORT Logger final {
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
		void debugMsg(const int line, const char* const file, const char* str, const char* msgType, va_list args);

		ILoggerStrategy* m_logStrategy = nullptr;;
	};
}