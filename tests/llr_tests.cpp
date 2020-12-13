#define REFERENCE_COUNTER_PROFOLER

#include<gtest/gtest.h>
#include<llr/llr.h>
#include<wnd/window.h>
#include "llr/VertexBuffer.h"
#include "llr/VertexArrayBuffer.h"
#include "llr/ConstantBuffer.h"
#include "llr/IndexBuffer.h"
#include "llr/Shader.h"
#include "llr/Texture2d.h"
#include "llr/Framebuffer.h"

#include "Common/Vector.h"

#include <vector>
#include <limits>

#define CONTROLL_SUM_EPSILON 0.1
#define BYTE_EPSILON .5 / static_cast<double>(UCHAR_MAX)

namespace {

#ifdef WIN32
	const std::string tmpDirLocation = "C:\\temp\\";
#else
	const std::string tmpDirLocation = "\\tmp\\";
#endif // WIN32

	

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

	const char* g_testShader1V = "#version 430 core\n"
		"layout(location = 0) in vec3 vertexPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(vertexPos, 1.0);\n"
		"}";


	const char* g_testShader1F = "#version 430 core\n"
		"uniform vec4 color = vec4(0,0,0,0);\n"
		"out vec4 colorOut;\n"
		"void main() {\n"
		"	 colorOut = color;\n"
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

void shaderVAOTest(llr::Shader shader, llr::VertexArrayBuffer vao, wnd::Window && window, std::function<void(const size_t, const size_t, const float checkPizel[4], const float*)> checkFunc) {
	window.makeContextCurrent();
	llr::Llr llr(window);


	float colorConstantDefault[4]{};
	float colorConstantData[]{ 0.2f, 0.4f, 0.6f, 0.8f };
	llr::ConstantBuffer colorModConstantBuffer(sizeof(colorConstantData));
	colorModConstantBuffer.Write(0, sizeof(colorConstantData), colorConstantData);

	shader.SetVertexArrayBuffer(vao);
	shader.SetConstantBuffer(colorModConstantBuffer, 0);

	RendererTest renderer(shader);

	window.addRenderer(&renderer);

	float* pixelsData = new float[window.getWidth() * window.getHeight() * 4];

	window.draw(); //dummy draw because of double buffer
	window.draw();
	llr.getFramebufferData(pixelsData);
	checkFunc(window.getWidth(), window.getHeight(), colorConstantData, pixelsData);

	delete[] pixelsData;
}


template<class T>
void texture2dTest(const size_t width, const size_t heigth, llr::ETextureFormat format, const std::vector<T> & dataVertex, const std::string& saveFile) {
	bool isSaveMode = !saveFile.empty();
	llr::Texture2D texture = llr::Texture2D(width, heigth, format);
	llr::Texture2D textureCheck = llr::Texture2D(width, heigth, format);

	texture.Write(0, width, 0, heigth, dataVertex.data());

	if (isSaveMode) {
		texture.Save(saveFile);
		textureCheck.Load(saveFile);
	}
	else {
		textureCheck = texture;
	}

	std::vector<T> checkVertex(dataVertex.size(), static_cast<T>(0));
	textureCheck.Read(0, width, 0, heigth, checkVertex.data());

	T checkSum = static_cast<T>(0);

	for (int i = 0; i < dataVertex.size(); ++i) {
		T diff = static_cast<T>(abs(dataVertex[i] - checkVertex[i]));
		checkSum += (isSaveMode && diff < BYTE_EPSILON) ? static_cast<T>(0) : diff;
	}
	EXPECT_TRUE(abs(checkSum) <= static_cast<T>(CONTROLL_SUM_EPSILON));

}


template<class T, int TS>
void texture2dTestFillCollor(const size_t width, const size_t heigth, llr::ETextureFormat format, Vector<T, TS> initVslue, const std::string& saveFile = "") {
	llr::Texture2D texture = llr::Texture2D(width, heigth, format);

	std::vector<T> dataVertex(width * heigth * TS);

	for (int i = 0; i < dataVertex.size(); i += TS) {
		for (int j = 0; j < TS; j++) {
			dataVertex[i + j] = initVslue[j];
		}
	}

	texture2dTest(width, heigth, format, dataVertex, saveFile);
	texture.Write(0, width, 0, heigth, dataVertex.data());
}

void texture2dTestWhiteNoise(const size_t width, const size_t heigth, llr::ETextureFormat format, const std::string & saveFile = "") {
	llr::Texture2D texture = llr::Texture2D(width, heigth, format);

	Size bpp = 0;
	if (format == llr::ETextureFormat::RGB) {
		bpp = 3;
	}
	else if(format == llr::ETextureFormat::RGBA) {
		bpp = 4;
	}
	else {
		//unsupported
		return;
	}

	std::vector<float> dataVertex(width * heigth * bpp);

	for (int i = 0; i < dataVertex.size(); i += bpp) {
		for (int j = 0; j < bpp; j++) {
			dataVertex[i + j] = (float)rand() / RAND_MAX;
		}
	}

	texture2dTest(width, heigth, format, dataVertex, saveFile);
	texture.Write(0, width, 0, heigth, dataVertex.data());
}

template<class T>
void ReferenceCounerTest(T vb) {
	ReferenceCounterProfiler::Get().Enable();
	ReferenceCounterProfiler::Get().Reset();
	{
		T vb0;
		EXPECT_EQ(ReferenceCounterProfiler::Get().Count(), 1);
		{
			llr::VertexBuffer vb1(vb);

			EXPECT_EQ(ReferenceCounterProfiler::Get().Count(), 2);

			llr::VertexBuffer vb2;
			vb2 = vb1;

			EXPECT_EQ(ReferenceCounterProfiler::Get().Count(), 3);

			llr::VertexBuffer vb3(std::move(vb2));

			EXPECT_EQ(ReferenceCounterProfiler::Get().Count(), 3);

			EXPECT_FALSE(vb2.IsValid());

		}
		EXPECT_EQ(ReferenceCounterProfiler::Get().Count(), 1);
	}
	EXPECT_EQ(ReferenceCounterProfiler::Get().Count(), 0);

	ReferenceCounterProfiler::Get().Disable();
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



TEST(llr_tests, ShaderVAO) {
	wnd::Window window(600, 600, "Unit Tests");

	llr::Shader shader = CreateShader({
		llr::ShaderSource(g_testShader0V, llr::EShaderSourceType::VERTEX),
		llr::ShaderSource(g_testShader0F, llr::EShaderSourceType::FRAGMENT)
		});

	EXPECT_TRUE(shader.IsValid());
	std::vector<float> dataVertex{ -1.f, -1.f, 0.f, -1., 1.f, 0.f, 1.f, -1.f, 0.f };
	std::vector<unsigned int> dataIndex{ 0, 1, 2 };

	const size_t dataVertexSizeInBytes = dataVertex.size() * sizeof(dataVertex[0]);
	const size_t dataIndexSizeInBytes = dataIndex.size() * sizeof(dataIndex[0]);

	


	llr::VertexBuffer vb(dataVertex.size(), llr::EDataType::FLOAT, 3);
	vb.Write(0, dataVertex.size(), dataVertex.data());

	llr::IndexBuffer ib(dataIndex.size(), llr::EDataType::UINT);
	ib.Write(0, dataIndex.size(), dataIndex.data());

	shader.SetIndexBuffer(ib);

	llr::VertexArrayBuffer vao;
	vao.SetVertexBuffer(vb, 0);
	vao.SetIndexBuffer(ib);


	shaderVAOTest(shader, vao, std::move(window), [](const size_t w, const size_t h, const float checkPizel[4], const float* data) {
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
		EXPECT_TRUE(abs(controllSum) < CONTROLL_SUM_EPSILON);
	});
}


TEST(llr_tests, Texture2D) {

	const size_t WIDTH = 800;
	const size_t HEIGHT = 600;

	wnd::Window window(600, 600, "Unit Tests");

	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RED, Vec1f{ {1.f} });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB, Vec3f{ { 1.f, 2.f, 3.f } });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGBA, Vec4f{ { 1.f, 2.f, 3.f, 4.f } });

	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RED, Vec1f{ {-12.f} });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB, Vec3f{ { -14.f, -0.5f, 66.f } });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGBA, Vec4f{ { -16.f, -0.8f, 13.f, 42.f } });


	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RED_INTEGER, Vec1i{ {1} });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB_INTEGER, Vec3i{ { 1, 2, 3 } });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGBA_INTEGER, Vec4i{ { 1, 2, 3, 4 } });

	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RED_INTEGER, Vec1i{ {-15} });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB_INTEGER, Vec3i{ { -18, -21, 98 } });
	texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGBA_INTEGER, Vec4i{ { -162251, -2, 2878, 455 } });


} 

TEST(llr_tests, Texture2D_IO) {
	//const size_t Widths[] = { 2, 50, 500, 1080, 3840 };
	//const size_t Heights[] = { 4, 25, 500, 1920, 2160 };

	const size_t Widths[] = { 2, 2, 50, 500};
	const size_t Heights[] = {1, 4, 25, 500};

	wnd::Window window(600, 600, "Unit Tests");

	for (int i = 0; i < sizeof(Widths) / sizeof(Widths[0]); ++i) {

		const size_t WIDTH = Widths[i];
		const size_t HEIGHT = Heights[i];

		texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB, Vec3f{ { 1.f, 0.f, 0.f } }, tmpDirLocation + "testRedColorRGB.png");
		texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB, Vec3f{ { 0.f, 1.f, 0.f} }, tmpDirLocation + "testGreenColorRGB.png");
		texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGB, Vec3f{ { 0.f, 0.f, 1.f} }, tmpDirLocation + "testBlueColorRGB.png");
		texture2dTestFillCollor(WIDTH, HEIGHT, llr::ETextureFormat::RGBA, Vec4f{ { 1.f, 1.f, 1.f, 1.f} }, tmpDirLocation + "testBlueAlphaRGBA.png");


		texture2dTestWhiteNoise(WIDTH, HEIGHT, llr::ETextureFormat::RGB, tmpDirLocation + "testNoiseRGB.png");
		texture2dTestWhiteNoise(WIDTH, HEIGHT, llr::ETextureFormat::RGB, tmpDirLocation + "testNoiseRGBA.png");
	}
}

TEST(llr_tests, Framebuffer) {


	const size_t WIDTH = 250;
	const size_t HEIGHT = 250;

	wnd::Window window(WIDTH, HEIGHT, "Unit Tests");

	llr::Shader shader = CreateShader({
		llr::ShaderSource(g_testShader1V, llr::EShaderSourceType::VERTEX),
		llr::ShaderSource(g_testShader1F, llr::EShaderSourceType::FRAGMENT)
		});

	EXPECT_TRUE(shader.IsValid());
	std::vector<float> dataVertex{ -1.f, -1.f, 0.f, -1., 1.f, 0.f, 1.f, -1.f, 0.f };
	std::vector<unsigned int> dataIndex{ 0, 1, 2 };

	const size_t dataVertexSizeInBytes = dataVertex.size() * sizeof(dataVertex[0]);
	const size_t dataIndexSizeInBytes = dataIndex.size() * sizeof(dataIndex[0]);




	llr::VertexBuffer vb(dataVertex.size(), llr::EDataType::FLOAT, 3);
	vb.Write(0, dataVertex.size(), dataVertex.data());

	llr::IndexBuffer ib(dataIndex.size(), llr::EDataType::UINT);
	ib.Write(0, dataIndex.size(), dataIndex.data());

	shader.SetIndexBuffer(ib);

	llr::VertexArrayBuffer vao;
	vao.SetVertexBuffer(vb, 0);
	vao.SetIndexBuffer(ib);

	llr::Framebuffer fb(WIDTH, HEIGHT);
	EXPECT_TRUE(fb.IsValid());

	llr::Texture2D texture = llr::Texture2D(WIDTH, HEIGHT, llr::ETextureFormat::RGBA);
	fb.SetTextures2d(texture, 0);

	shader.SetFramebuffer(fb);


	float colorConstantDefault[4]{};
	float colorConstantData[]{ 0.2f, 0.4f, 0.6f, 0.8f };
	const float red[4] = { 0.98f,0.f,0.f,1.f };
	const float green[4] = { 0,0.95,0,1 };
	const float blue[4] = { 0,0,0.92,1 };
	float* pixelsData = new float[600 * 600 * 4];

	shader.SetConstant("color", red[0], red[1], red[2], red[3]);
	shader.SetVertexBuffer(vb, 0);
	shader.SetIndexBuffer(ib);

	RendererTest renderer(shader);

	window.addRenderer(&renderer);

	window.draw(); 


	std::vector<float> textureData(WIDTH * HEIGHT * 4, 0.f);
	auto dataCheck = [&textureData, WIDTH, HEIGHT](const float checkPizel[4]) {
		float controllSum = 0.f;
		const float* data = textureData.data();
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; ++j) {
				const float* pixel = data + ((WIDTH * j + HEIGHT - i - 1) * 4);
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
		EXPECT_TRUE(abs(controllSum) < CONTROLL_SUM_EPSILON);
	};

	texture.Read(0, WIDTH, 0, HEIGHT, textureData.data());

	dataCheck(red);
}
