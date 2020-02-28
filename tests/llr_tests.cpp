#include<gtest/gtest.h>
#include<llr/llr.h>
#include<wnd/window.h>
#include "llr/VertexBuffer.h"
#include "llr/ConstantBuffer.h"
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
		"uniform vec4 color = vec4(0,0,0,0);\n"
		"layout(std140, binding = 0) uniform ColorMod {"
		"	vec4 mod;"
		"} uColorMod;"
		"out vec4 colorOut;\n"
		"void main() {\n"
		"	 colorOut = color + uColorMod.mod;\n"
		"}";


	struct TestConstBuffer0 {
		TestConstBuffer0() = default;
		TestConstBuffer0(const float * f) {
			memcpy(Fl, f, sizeof(Fl));
		}

		bool operator==(const TestConstBuffer0& r) const{
			return !memcmp(Fl, r.Fl, sizeof(Fl));
		}

		float Fl[4];
	};

	struct TestConstBuffer1 {
		TestConstBuffer1(const int i, const float* f, const unsigned int ui) : Int(i), UInt(ui) {
			memcpy(Fl, f, sizeof(Fl));
		}

		bool operator==(const TestConstBuffer1 & r) const {
			return !memcmp(Fl, r.Fl, sizeof(Fl)) && Int == r.Int && UInt == r.UInt;
		}

		int Int;
		float Fl[4];
		unsigned int UInt;
	};
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

llr::Shader CreateShader(std::list<llr::ShaderSource> shaderSources) {
	llr::Shader shader(shaderSources);
	EXPECT_TRUE(shader.IsValid());
	return shader;
}


void simpleShaderTest(const char * vertShader, const char* fragShader, const std::vector<float> & dataVertex, const std::vector<unsigned int> & dataIndex, const size_t w, const size_t h, std::function<void(const size_t, const size_t, const float checkPizel[4], const float*)> checkFunc) {
	wnd::Window window(w, h, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	llr::Shader shader = CreateShader({
		llr::ShaderSource(vertShader, llr::EShaderSourceType::VERTEX),
		llr::ShaderSource(fragShader, llr::EShaderSourceType::FRAGMENT) 
		});

	EXPECT_TRUE(shader.IsValid());

	const size_t dataVertexSizeInBytes = dataVertex.size() * sizeof(dataVertex[0]);
	const size_t dataIndexSizeInBytes = dataIndex.size() * sizeof(dataIndex[0]);

	llr::VertexBuffer vb(dataVertex.size(), llr::EDataType::FLOAT, 3);
	vb.Write(0, dataVertex.size(), dataVertex.data());

	llr::IndexBuffer ib(dataIndex.size(), llr::EDataType::UINT);
	ib.Write(0, dataIndex.size(), dataIndex.data());

	float colorConstantDefault[4]{};
	float colorConstantData[]{ 0.2f, 0.4f, 0.6f, 0.8f };
	llr::ConstantBuffer colorModConstantBuffer(sizeof(colorConstantData));
	colorModConstantBuffer.Write(0, sizeof(colorConstantData), colorConstantData);

	shader.SetConstantBuffer(colorModConstantBuffer, 0);
	shader.SetVertexBuffer(vb, 0);
	shader.SetIndexBuffer(ib);

	RendererTest renderer(shader);

	window.addRenderer(&renderer);

	
	

	const float red[4] = { 1.f,0.f,0.f,1.f };
	const float green[4] = { 0,1,0,1 };
	const float blue[4] = { 0,0,1,1 };
	float* pixelsData = new float[w * h * 4];

	window.draw(); //dummy draw because of double buffer
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(w, h, colorConstantData, pixelsData);

	// Clear color modificator buffer
	colorModConstantBuffer.Write(0, sizeof(colorConstantDefault), colorConstantDefault);

	shader.SetConstant("color", red[0], red[1], red[2], red[3]);
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(w, h, red, pixelsData);

	
	shader.SetConstant("color", green[0], green[1], green[2], green[3]);
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(w, h, green, pixelsData);

	
	shader.SetConstant("color", blue[0], blue[1], blue[2], blue[3]);
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

TEST(llr_tests, ConstantBuffer) {
	wnd::Window window(800, 600, "Unit Tests");
	window.makeContextCurrent();
	llr::Llr llr(window);

	float testFloatArr[]{ 1.f, 2.f, 3.f, 4.f };
	TestConstBuffer0 testData0(testFloatArr);
	llr::ConstantBuffer cb(sizeof(testData0));

	cb.Write(0, sizeof(testData0), &testData0);

	TestConstBuffer0 checkData;
	cb.Read(0, sizeof(testData0), &checkData);


	EXPECT_EQ(testData0, checkData);
}

TEST(llr_tests, Shader) {
	// TODO: Fix test case. Use different resolution
	simpleShaderTest(g_testShader0V, g_testShader0F
		, { -1.f, -1.f, 0.f, -1., 1.f, 0.f, 1.f, -1.f, 0.f }
		, { 0, 1, 2 }
		, 600, 600, [](const size_t w, const size_t h, const float checkPizel[4], const float* data) {
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