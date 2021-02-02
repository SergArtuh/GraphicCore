#include "gapi.h"
#include "wnd/window.h"
#include "llr/Shader.h"

#include "Context.h"
#include "Scene.h"
#include "Shader.h"
#include "RenderPass.h"
#include "RenderPassStage.h"
#include "RenderPassConstantInput.h"
#include "RenderPassInstanceArrayInput.h"
#include "RenderPassOutput.h"
#include "Camera.h"
#include "Geometry.h"

namespace gapi {
	Gapi::Gapi(wnd::Window& window) : m_llr(window) {
		
	}

	Gapi::Gapi(const Gapi& r) : m_llr(r.m_llr) {
		
	}

	Gapi::~Gapi() {}

	PContext Gapi::CreateContext()
	{
		return new Context(m_llr.GetWindow());
	}

	void Gapi::DeleteContext(PContext context)
	{
		if (context) {
			delete context;
		}
	}

	PScene Gapi::CreateScene() {
		return new Scene;
	}

	void Gapi::DeleteScene(PScene scene) {
		if (scene) {
			delete scene;
		}
	}

	PShader Gapi::CreateShader(const std::list<ShaderSource> & sources) {
		return new Shader(sources);
	}

	void Gapi::DeleteShader(PShader shader) {
		if (shader) {
			delete shader;
		}
	}

	PRenderPass Gapi::CreateRenderPass(PShader shader) {
		return new RenderPass(shader);
	}

	void Gapi::DeleteRenderPass(PRenderPass renderPass) {
		if (renderPass) {
			delete renderPass;
		}
	}

	void Gapi::AddRenderPassStage(PRenderPass renderPass, PRenderPassStage stage) {
		renderPass->AddRenderPassStage(stage);
	}

	PRenderPassConstantInput Gapi::CreateRenderPassInput(Size size)
	{
		return new RenderPassConstantInput(size);
	}

	void Gapi::DeleteRenderPassInput(PRenderPassConstantInput renderPassInput) {
		if (renderPassInput) {
			delete renderPassInput;
		}
	}

	PRenderPassInstanceArrayInput Gapi::CreateRenderPassInstanceArrayInput(CSize size, EDataType type, CSize count) {
		return new RenderPassInstanceArrayInput(size, type, count);
	}

	void Gapi::DeleteRenderPassInstanceArrayInput(PRenderPassInstanceArrayInput instanceArrayInput) {
		if (instanceArrayInput) {
			delete instanceArrayInput;
		}
	}

	PRenderPassOutput Gapi::CreateRenderPassOutput() {
		return new RenderPassOutput;
	}

	void Gapi::DeleteRenderPassOutput(PRenderPassOutput renderPassOutput) {
		if (renderPassOutput) {
			delete renderPassOutput;
		}
	}

	PTexture2D Gapi::CreateTexture2d(CSize width, CSize height, ETextureFormat format) {
		return new Texture2D(width, height, format);
	}

	void Gapi::DeleteTexture2d(PTexture2D texture2d) {
		if (texture2d) {
			delete texture2d;
		}
	}

	PRenderPassStage Gapi::CreateRenderPassStage()
	{
		return new RenderPassStage();
	}

	void Gapi::DeleteRenderPassStage(PRenderPassStage stage)
	{
		if (stage) {
			delete stage;
		}
	}

	void Gapi::ContextAddRenderPass(PContext context, PRenderPass renderPass)
	{
		context->AddRenderPass(renderPass);
	}

	void Gapi::ContextRemoveRenderPass(PContext context, PRenderPass renderPass)
	{
		context->RemoveRenderPass(renderPass);
	}


	PCamera Gapi::CreateCamera(float fow, float aspect, float near, float far) {
		return new Camera(fow, aspect, near, far);
	}

	void Gapi::DeleteCamera(PCamera camera) {
		if (camera) {
			delete camera;
		}
	}

	PGeometry Gapi::CreateGeometry(std::vector<float> vertices3f, std::vector<UI32> indexes) {
		return new Geometry(vertices3f, indexes);
	}

	void Gapi::DeleteGeometry(PGeometry geometry) {
		if (geometry) {
			delete geometry;
		}
	}
	void Gapi::Draw(PContext context, PScene scene)
	{
		context->Draw(scene);
	}
}