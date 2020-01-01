#pragma once

#define LLR_EXPORT __declspec(dllexport)

#define LLR_ERROR(str, ...) llrError((str), __VA_ARGS__)
#define LLR_WARNING(str, ...) llrWarning((str), __VA_ARGS__)
#define LLR_INFO(str, ...) llrInfo((str), __VA_ARGS__)

namespace llr {

	void llrError(const char* str, ...);
	void llrWarning(const char* str, ...);
	void llrInfo(const char* str, ...);

	class LLR_EXPORT llr {
		public:
		llr() {
		}
	};
}
