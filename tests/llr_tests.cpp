#include<gtest/gtest.h>
#include<llr/llr.h>
#include<wnd/window.h>
#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

#include <vector>

template<class T, class dataType> 
void bufferTest(size_t dataCount, dataType testValue0, dataType testValue1, dataType testValue2) {
	const size_t dataNewCount = dataCount / 10;
	const size_t dataOffset = dataCount / 20;

	std::vector<dataType> data(dataCount, testValue0);
	std::vector<dataType> checkData(dataCount, static_cast<dataType>(0));

	const size_t dataSizeInBytes = dataCount * sizeof(data[0]);

	T vb(dataSizeInBytes);


	vb.Write(0, dataSizeInBytes, data.data());
	vb.Read(0, dataSizeInBytes, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));


	std::fill(data.begin(), data.begin() + dataNewCount, testValue1);
	std::fill(checkData.begin(), checkData.end(), 0.);

	vb.Write(0, dataSizeInBytes, data.data());
	vb.Read(0, dataSizeInBytes, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));


	std::fill(data.begin() + dataOffset, data.begin() + dataOffset + dataNewCount, testValue2);
	std::fill(checkData.begin(), checkData.end(), 0.);

	vb.Write(0, dataSizeInBytes, data.data());
	vb.Read(0, dataSizeInBytes, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));
}

TEST(llr_tests, VertexBuffer) {
	wnd::Window window(800, 600, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	bufferTest< llr::VertexBuffer>(2048, 1.f, 2.f, 3.f);
	bufferTest< llr::VertexBuffer>(1e6, 1.f, 2.f, 3.f);
}


TEST(llr_tests, IndexBuffer) {
	wnd::Window window(800, 600, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	bufferTest< llr::IndexBuffer>(2048, 1U, 2U, 3U);
	bufferTest< llr::IndexBuffer>(1e6, 1, 2, 3);
}