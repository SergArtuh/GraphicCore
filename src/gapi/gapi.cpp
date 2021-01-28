#include "gapi.h"
#include "wnd/window.h"
#include "llr/Shader.h"

#include "Context.h"
#include "Scene.h"
#include "Shader.h"
#include "RenderPass.h"
#include "RenderPassStage.h"
#include "RenderPassInput.h"
#include "RenderPassOutput.h"
#include "Camera.h"
#include "Geometry.h"

namespace gapi {
	Gapi::Gapi(wnd::Window& window) : m_llr(window) {
		
	}

	Gapi::Gapi(const Gapi& r) : m_llr(r.m_llr) {
		
	}

	Gapi::~Gapi() {}

	Context* Gapi::CreateContext()
	{
		return new Context(m_llr.GetWindow());
	}

	void Gapi::DeleteContext(Context* context)
	{
		if (context) {
			delete context;
		}
	}

	Scene* Gapi::CreateScene() {
		return new Scene;
	}

	void Gapi::DeleteScene(Scene * scene) {
		if (scene) {
			delete scene;
		}
	}

	Shader* Gapi::CreateShader(const std::list<ShaderSource> & sources) {
		return new Shader(sources);
	}

	void Gapi::DeleteShader(Shader* shader) {
		if (shader) {
			delete shader;
		}
	}

	RenderPass* Gapi::CreateRenderPass(Shader * shader) {
		return new RenderPass(shader);
	}

	void Gapi::DeleteRenderPass(RenderPass* renderPass) {
		if (renderPass) {
			delete renderPass;
		}
	}

	void Gapi::AddRenderPassStage(RenderPass* renderPass, RenderPassStage* stage) {
		renderPass->AddRenderPassStage(stage);
	}

	RenderPassInput * Gapi::CreateRenderPassInput(Size size)
	{
		return new RenderPassInput(size);
	}

	void Gapi::DeleteRenderPassInput(RenderPassInput * renderPassInput) {
		if (renderPassInput) {
			delete renderPassInput;
		}
	}

	RenderPassOutput* Gapi::CreateRenderPassOutput() {
		return new RenderPassOutput;
	}

	void Gapi::DeleteRenderPassOutput(RenderPassOutput* renderPassOutput) {
		if (renderPassOutput) {
			delete renderPassOutput;
		}
	}

	PTexture2D Gapi::CreateTexture2d(CSize width, CSize height, ETextureFormat format) {
		return new Texture2D(width, height, format);
	}

	void Gapi::DeleteTexture2d(Texture2D* texture2d) {
		if (texture2d) {
			delete texture2d;
		}
	}

	RenderPassStage* Gapi::CreateRenderPassStage()
	{
		return new RenderPassStage();
	}

	void Gapi::DeleteRenderPassStage(RenderPassStage* stage)
	{
		if (stage) {
			delete stage;
		}
	}

	void Gapi::SetRenderPassStageInput(RenderPassStage* stage, RenderPassInput* renderPassInput, UI32 location)
	{
		stage->SetInput(renderPassInput, location);
	}

	void Gapi::ContextAddRenderPass(Context* context, RenderPass* renderPass)
	{
		context->AddRenderPass(renderPass);
	}

	void Gapi::ContextRemoveRenderPass(Context* context, RenderPass* renderPass)
	{
		context->RemoveRenderPass(renderPass);
	}


	Camera* Gapi::CreateCamera(float fow, float aspect, float near, float far) {
		return new Camera(fow, aspect, near, far);
	}

	void Gapi::DeleteCamera(Camera* camera) {
		if (camera) {
			delete camera;
		}
	}

	Geometry* Gapi::CreateGeometry(std::vector<float> vertices3f, std::vector<UI32> indexes) {
		return new Geometry(vertices3f, indexes);
	}

	void Gapi::DeleteGeometry(Geometry* geometry) {
		if (geometry) {
			delete geometry;
		}
	}
	void Gapi::Draw(Context* context, Scene* scene)
	{
		context->Draw(scene);
	}
}