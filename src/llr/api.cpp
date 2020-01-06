#include "api.h"

#include <GL/glew.h>
#include <Windows.h>

#include<vector>

#include <stdio.h>

#include "wnd/window.h"


#define MAX_BUFFER_SIZE 2048


namespace llr {

	void debugMsg(const char* str, const char * msgType, va_list args) {
		std::vector<char> buffer(MAX_BUFFER_SIZE);

		snprintf(buffer.data(), buffer.size(), "[ LLR %s ]\t", msgType);

		const size_t shift = strlen(buffer.data());

		vsnprintf(buffer.data() + shift, MAX_BUFFER_SIZE, str, args);

		OutputDebugString(buffer.data());
		OutputDebugString("\n");
	}

	void errorMsg(const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(str, "Error", args);
		va_end(args);
	}

	void warningMsg(const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(str, "Warning", args);
		va_end(args);
	}

	void infoMsg(const char* str, ...) {
		va_list args;
		va_start(args, str);
		debugMsg(str, "Info", args);
		va_end(args);
	}
}