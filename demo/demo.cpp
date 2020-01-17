#include <GraphicCore/GraphicCore.h>

namespace {
	float vertices[] = { -1.f, -1.f, 0.f, -1., 1.f, 0.f, 1.f, -1.f, 0.f };
	unsigned int indexes[] = { 0, 1, 2 };

	const char * g_testShader0V = "#version 430 core\n"
		"layout(location = 0) in vec3 vertexPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(vertexPos, 1.0);\n"
		"}";

	const char * g_testShader0F = "#version 430 core\n"
		"uniform vec3 color = vec3(1,1,1);\n"
		"out vec3 colorOut;\n"
		"void main() {\n"
		"	 colorOut = color;\n"
		"}";
}

template<class T, int N>
constexpr size_t arrSize(T (&)[N]) { return N; };

class App {
	using Window = wnd::Window;
	using Gapi = gapi::Gapi;
	using Shader = gapi::Shader;
	using RenderPass = gapi::RenderPass;
	using Scene = gapi::Scene;
	using Geometry = gapi::Geometry;

public:

	void Init() {
		m_window = CreateWindow(256, 256, "Demo");
		m_gapi = CreateGapi(m_window);
		m_scene = CreateScene(m_gapi);
		m_shader = CreateShader(m_gapi, 2, 1, g_testShader0V, 2, g_testShader0F);
		m_renderPass = CreateRenderPass(m_gapi, m_shader);

		m_geometry = CreateGeometry(m_gapi, vertices, arrSize(vertices), indexes, arrSize(indexes));

		AddRenderPass(m_gapi, m_renderPass);
		SceneAddGeometry(m_scene, m_geometry);
	}

	void Run() {
		Draw(m_gapi, m_scene);
	}

private:
	Window * m_window = nullptr;
	Gapi * m_gapi = nullptr;
	Shader* m_shader = nullptr;
	RenderPass* m_renderPass = nullptr;
	Scene* m_scene = nullptr;
	Geometry * m_geometry = nullptr;
};

void main() {
	App app;
	app.Init();
	app.Run();
}