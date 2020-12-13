#pragma once
#include "api.h"
#include "types.h"
#include <vector>


namespace imgio {

	struct ImgData {
		Size Width;
		Size Height;
		UI32 BPP;

		std::vector<float> PixelData;
		std::string Path;
	};

	COMMON_EXPORT ImgData loadImage(const std::string& path);

	COMMON_EXPORT void saveImage(const ImgData && imgData);
};