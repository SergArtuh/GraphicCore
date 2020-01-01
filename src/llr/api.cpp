#include "api.h"

#include <Windows.h>

#include<vector>

#include <stdio.h>


#define MAX_BUFFER_SIZE 2048


namespace llr {

	void llrDebugMsg(const char* str, const char * msgType, ...) {
		std::vector<char> buffer(MAX_BUFFER_SIZE);

		snprintf(buffer.data(), buffer.size(), "[ LLR %s ]\t", msgType);

		const size_t shift = strlen(buffer.data());

		va_list args;
		va_start(args, str);
		vsnprintf(buffer.data() + shift, MAX_BUFFER_SIZE, str, args);

		OutputDebugString(buffer.data());
		OutputDebugString("\n");

		va_end(args);
	}

	void llrError(const char* str, ...) {
		va_list args;
		va_start(args, str);
		llrDebugMsg(str, "Error", args);
		va_end(args);
	}

	void llrWarning(const char* str, ...) {
		va_list args;
		va_start(args, str);
		llrDebugMsg(str, "Warning", args);
		va_end(args);
	}

	void llrInfo(const char* str, ...) {
		va_list args;
		va_start(args, str);
		llrDebugMsg(str, "Info", args);
		va_end(args);
	}
}