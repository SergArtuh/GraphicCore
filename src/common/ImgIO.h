#pragma once
#include "api.h"
#include "types.h"
#include <vector>


namespace imgio {

	struct ImgData {
		Size Width = 0;
		Size Height = 0;
		UI32 BPP = 0;

		std::vector<float> PixelData;
		std::string Path = "";

		operator bool() {
			return Width > 0 && Height > 0 && BPP > 0;
		}
	};

	COMMON_EXPORT ImgData loadImage(const std::string& path);

	COMMON_EXPORT void saveImage(const ImgData && imgData);
};