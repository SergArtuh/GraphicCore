#include<gtest/gtest.h>
#include<llr/llr.h>
#include<wnd/window.h>
#include "llr/VertexBuffer.h"

#include <vector>



TEST(llr_tests, VertexBuffer) {
	wnd::Window window(800, 600, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	const size_t dataCount = 128;
	const size_t dataNewCount = 5;
	const size_t dataOffset= 50;

	std::vector<float> data(dataCount, 7.f);
	std::vector<float> checkData(dataCount, 0.f);

	const size_t dataSizeInBytes = dataCount * sizeof(data[0]);

	llr::VertexBuffer vb(dataSizeInBytes);


	vb.Write(0, dataSizeInBytes, data.data());
	vb.Read(0, dataSizeInBytes, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));


	std::fill(data.begin(), data.begin() + dataNewCount, 2.);
	std::fill(checkData.begin(), checkData.end(), 0.);

	vb.Write(0, dataSizeInBytes, data.data());
	vb.Read(0, dataSizeInBytes, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));


	std::fill(data.begin() + dataOffset, data.begin() + dataOffset + dataNewCount, 3.);
	std::fill(checkData.begin(), checkData.end(), 0.);

	vb.Write(0, dataSizeInBytes, data.data());
	vb.Read(0, dataSizeInBytes, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));

}