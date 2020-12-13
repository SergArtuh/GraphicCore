#pragma once
#include "ImgIO.h"

#include <png.h>

namespace imgio {
	

	void savePng(const ImgData&& imgData) {
		FILE* fp = fopen(imgData.Path.c_str(), "wb");
		if (!fp)
		{
			//TODO: log warning
			return;
		}

		png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (!png_ptr) {
			//TODO: log warning
			return;
		}
		

		png_infop png_info;
		if (!(png_info = png_create_info_struct(png_ptr))) {
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			//TODO: log warning
			return;
		}

		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			return;
		}

		png_init_io(png_ptr, fp);

		if (!(imgData.BPP == 3 || imgData.BPP == 4)) {
			//TODO: UNSUPPORTED
			return;
		}

		int colorType = [&imgData]() {
			switch (imgData.BPP)
			{
				case 3: return PNG_COLOR_TYPE_RGB;
				case 4: return PNG_COLOR_TYPE_RGBA;
				default: return -1;
			}}();
		png_set_IHDR(png_ptr, png_info, imgData.Width, imgData.Height, 8, colorType,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);

		std::vector<UByte> data(imgData.Width * imgData.Height * imgData.BPP);
		std::vector<UByte  * > rows(imgData.Height);


		for (int i = 0; i < imgData.Height; ++i) {
			for (int j = 0; j < imgData.Width ; ++j) {
				for (int k = 0; k < imgData.BPP; ++k) {
					Size idx = (i * imgData.Width + j) * imgData.BPP + k;
					data[idx] = static_cast<unsigned char>(roundf(imgData.PixelData[idx] * 255.f));
				}
				
			}
			rows[imgData.Height - i - 1] = data.data() + (i * imgData.Width * imgData.BPP);
		}

		png_set_rows(png_ptr, png_info, rows.data());
		png_write_png(png_ptr, png_info, PNG_TRANSFORM_IDENTITY, nullptr);
		png_write_end(png_ptr, png_info);

		png_destroy_write_struct(&png_ptr, nullptr);
		fclose(fp);
	}

	ImgData loadPng(const std::string & path) {
		ImgData imgData; 
		imgData.Path = path;

		FILE* fp = fopen(imgData.Path.c_str(), "rb");
		if (!fp)
		{
			//TODO: log warning
			return imgData;
		}


		UByte header[9];
		CSize headerN = 8;
		fread(header, 1, headerN, fp);
		int is_png = !png_sig_cmp(header, 0, headerN);
		if (!is_png) {
			//TODO: log warning
			return imgData;
		}


		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (!png_ptr) {
			//TODO: log warning
			return imgData;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			png_destroy_read_struct(&png_ptr, nullptr, nullptr);
			//TODO: log warning
			return imgData;
		}

		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr,
				(png_infopp)NULL);
			//TODO: log warning
			return imgData;
		}

		png_init_io(png_ptr, fp);
		png_set_sig_bytes(png_ptr, headerN);

		png_read_info(png_ptr, info_ptr);
		png_uint_32 width, height;
		int bit_depth, color_type, interlace_type, compression_type, filter_method;
		png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, \
			& interlace_type, NULL, NULL);

		imgData.Width = width;
		imgData.Height = height;
		imgData.BPP = [&color_type]() {
			switch (color_type)
			{
			case PNG_COLOR_TYPE_RGB: return 3;
			case PNG_COLOR_TYPE_RGBA: return 4;
			default: return -1;
			}}();

		imgData.PixelData.resize(imgData.Width * imgData.Height * imgData.BPP);

		std::vector<UByte* > rows(imgData.Height);
		std::vector<UByte> data(imgData.Width * imgData.Height * imgData.BPP);
		for (int i = 0; i < rows.size(); ++i) {
			rows[imgData.Height - i - 1] = data.data() +i * imgData.Width * imgData.BPP;
		}

		png_set_rows(png_ptr, info_ptr, rows.data());
		// Read png image data and save in row pointer
		// After reading the image, you can deal with the image data with row pointers
		png_read_image(png_ptr, rows.data());


		for (int i = 0; i < imgData.Height; ++i) {
			for (int j = 0; j < imgData.Width; ++j) {
				for (int k = 0; k < imgData.BPP; ++k) {
					Size idx = (i * imgData.Width + j) * imgData.BPP + k;
					imgData.PixelData[idx] = static_cast<float>(data[idx]) / 255.f;
				}

			}
		}



		png_read_end(png_ptr, end_info);
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

		fclose(fp);

		return imgData;
	}

	ImgData loadImage(const std::string& path) {
		return loadPng(path);
	}

	void saveImage(const ImgData&& imgData) {

		savePng(std::forward<const ImgData>(imgData));
	}
}

