#include "api.h"

#include <GL/glew.h>
#include <Windows.h>

#include<vector>

#include <stdio.h>

#include "wnd/window.h"


#define MAX_BUFFER_SIZE 2048


namespace llr {

	void debugMsg(const int line, const char* const file, const char* str, const char * msgType, va_list args) {
		std::vector<char> buffer(MAX_BUFFER_SIZE);

		snprintf(buffer.data(), buffer.size(), "[ LLR %s ] at line: %d, file %s:\t", msgType, line, file);

		const size_t shift = strlen(buffer.data());

		vsnprintf(buffer.data() + shift, MAX_BUFFER_SIZE, str, args);

		OutputDebugString(buffer.data());
		OutputDebugString("\n");
	}

	void errorMsg(const int line, const char* const file, const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(line, file, str, "Error", args);
		va_end(args);
	}

	void warningMsg(const int line, const char* const file, const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(line, file, str, "Warning", args);
		va_end(args);
	}

	void infoMsg(const int line, const char* const file, const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(line, file, str, "Info", args);
		va_end(args);
	}
}