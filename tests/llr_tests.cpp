#include<gtest/gtest.h>
#include<llr/llr.h>
#include<wnd/window.h>
#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"
#include "llr/Shader.h"

#include <vector>

#define CONTROLL_SUM_EPSILON 1e-5

namespace {
	const char* g_testShader0V = "#version 430 core\n"
		"layout(location = 0) in vec3 vertexPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(vertexPos, 1.0);\n"
		"}";

	const char* g_testShader0F = "#version 430 core\n"
		"uniform vec3 color = vec3(1,1,1);\n"
		"out vec3 colorOut;\n"
		"void main() {\n"
		"	 colorOut = color;\n"
		"}";
}


class RendererTest final : public wnd::IRenderer
{
public:
	RendererTest(llr::Shader & shader) : m_shader(shader) {}

	


private:
	
	void OnRender(wnd::Window& window) override {
		m_shader.Draw();
	}
	llr::Shader & m_shader;
};

template<class T> 
T CreateBuffer(size_t dataCount, llr::EDataType dataType) {
	T buffer(dataCount, dataType);
	EXPECT_TRUE(buffer.IsValid());
	return buffer;
}

template<class T, class DT> 
void bufferTest(size_t dataCount, DT testValue0, DT testValue1, DT testValue2, llr::EDataType dataType) {
	const size_t dataNewCount = dataCount / 10;
	const size_t dataOffset = dataCount / 20;

	std::vector<DT> data(dataCount, testValue0);
	std::vector<DT> checkData(dataCount, static_cast<DT>(0));

	T vb = CreateBuffer<T>(dataCount, dataType);
	EXPECT_TRUE(vb.IsValid());


	vb.Write(0, dataCount, data.data());
	vb.Read(0, dataCount, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));


	std::fill(data.begin(), data.begin() + dataNewCount, testValue1);
	std::fill(checkData.begin(), checkData.end(), 0.);

	vb.Write(0, dataCount, data.data());
	vb.Read(0, dataCount, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));


	std::fill(data.begin() + dataOffset, data.begin() + dataOffset + dataNewCount, testValue2);
	std::fill(checkData.begin(), checkData.end(), 0.);

	vb.Write(0, dataCount, data.data());
	vb.Read(0, dataCount, checkData.data());

	EXPECT_TRUE(std::equal(data.begin(), data.end(), checkData.begin()));
}

void simpleShaderTest(const char * vertShader, const char* fragShader, const std::vector<float> & dataVertex, const std::vector<unsigned int> & dataIndex, const size_t w, const size_t h, std::function<void(const size_t, const size_t, const float checkPizel[4], const float*)> checkFunc) {
	wnd::Window window(w, h, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	llr::Shader shader({
		llr::ShaderSource(vertShader, llr::EShaderSourceType::VERTEX),
		llr::ShaderSource(fragShader, llr::EShaderSourceType::FRAGMENT) 
		});

	const size_t dataVertexSizeInBytes = dataVertex.size() * sizeof(dataVertex[0]);
	const size_t dataIndexSizeInBytes = dataIndex.size() * sizeof(dataIndex[0]);

	llr::VertexBuffer vb(dataVertex.size(), llr::EDataType::FLOAT, 3);
	vb.Write(0, dataVertex.size(), dataVertex.data());

	llr::IndexBuffer ib(dataIndex.size(), llr::EDataType::UINT);
	ib.Write(0, dataIndex.size(), dataIndex.data());

	shader.SetVertexBuffer(vb, 0);
	shader.SetIndexBuffer(ib);

	RendererTest renderer(shader);

	window.addRenderer(&renderer);

	
	

	const float red[4] = { 1.f,0.f,0.f,0.f };
	const float green[4] = { 0,1,0,0 };
	const float blue[4] = { 0,0,1,0 };
	float* pixelsData = new float[w * h * 4];


	shader.SetConstant("color", red[0], red[1], red[2]);
	window.draw(); //dummy draw because of double buffer
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(w, h, red, pixelsData);

	
	shader.SetConstant("color", green[0], green[1], green[2]);
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(w, h, green, pixelsData);

	
	shader.SetConstant("color", blue[0], blue[1], blue[2]);
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(w, h, blue, pixelsData);

	delete[] pixelsData;
}



TEST(llr_tests, VertexBuffer) {
	wnd::Window window(800, 600, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	bufferTest<llr::VertexBuffer>(2048, 1.f, 2.f, 3.f, llr::EDataType::FLOAT);
	bufferTest<llr::VertexBuffer>(1e6, 1.f, 2.f, 3.f, llr::EDataType::FLOAT);
	bufferTest<llr::VertexBuffer>(1e6, -1.f, -2.f, -3.f, llr::EDataType::FLOAT);

	
	bufferTest< llr::VertexBuffer>(2048, 1U, 2U, 3U, llr::EDataType::UINT);
	bufferTest< llr::VertexBuffer>(2048, -1, -2, -3, llr::EDataType::INT);
}


TEST(llr_tests, IndexBuffer) {
	wnd::Window window(800, 600, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	bufferTest< llr::IndexBuffer>(2048, 1U, 2U, 3U, llr::EDataType::UINT);
	bufferTest< llr::IndexBuffer>(1e6, 1, 2, 3, llr::EDataType::UINT);
}

TEST(llr_tests, Shader) {
	simpleShaderTest(g_testShader0V, g_testShader0F
		, { -1.f, -1.f, 0.f, -1., 1.f, 0.f, 1.f, -1.f, 0.f }
		, { 0, 1, 2 }
		, 128, 128, [](const size_t w, const size_t h, const float checkPizel[4], const float* data) {
		float controllSum = 0.f;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; ++j) {
				const float* pixel = data + ((w * j + h - i - 1) * 4);
				if (j < i) {
					controllSum += checkPizel[0] - pixel[0];
					controllSum += checkPizel[1] - pixel[1];
					controllSum += checkPizel[2] - pixel[2];
					controllSum += checkPizel[3] - pixel[3];
				}
				else {
					controllSum += pixel[0];
					controllSum += pixel[1];
					controllSum += pixel[2];
					controllSum += pixel[3];
				}
			}
		}
		EXPECT_TRUE(controllSum < CONTROLL_SUM_EPSILON);
	});

}