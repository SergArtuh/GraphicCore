#pragma once
#include "api.h"
#include "llr/llr.h"

#include "enum.h"

#include "Shader.h"

#include <vector>
#include <list>

namespace wnd {
	class Window;
}


namespace gapi {
	class Context;
	class Scene;
	class RenderPass;
	class RenderPassStage;
	class RenderPassInput;
	class RenderPassOutput;
	class Camera;
	class Geometry;
	class Texture2D;


	class GAPI_EXPORT Gapi final {
	public:
		Gapi(wnd::Window & window);
		Gapi(const Gapi & gapi);

		~Gapi();

		Context* CreateContext();

		void DeleteContext(Context * context);

		Scene* CreateScene();

		void DeleteScene(Scene*);


		Shader* CreateShader(const std::list< ShaderSource> & sources);

		void DeleteShader(Shader * shader);
		

		RenderPassInput * CreateRenderPassInput(Size size);

		void DeleteRenderPassInput(RenderPassInput * renderPassInput);


		RenderPassOutput* CreateRenderPassOutput();

		void DeleteRenderPassOutput(RenderPassOutput* renderPassOutput);


		Texture2D* CreateTexture2d(CSize width, CSize height, ETextureFormat format);

		void DeleteTexture2d(Texture2D * texture2d);


		RenderPassStage * CreateRenderPassStage();

		void DeleteRenderPassStage(RenderPassStage * stage);

		void SetRenderPassStageInput(RenderPassStage* renderPass, RenderPassInput* renderPassInput, UI32 location);


		RenderPass* CreateRenderPass(Shader * shader);

		void DeleteRenderPass(RenderPass * renderPass);

		void AddRenderPassStage(RenderPass* renderPass, RenderPassStage* stage);


		void ContextAddRenderPass(Context* context, RenderPass* renderPass);

		void ContextRemoveRenderPass(Context* context, RenderPass* renderPass);

		[[deprecated]]
		Camera* CreateCamera(float fow, float aspect, float near, float far);

		[[deprecated]]
		void DeleteCamera(Camera * camera);

		Geometry* CreateGeometry(std::vector<float> vertices3f, std::vector<UI32> indexes);

		void DeleteGeometry(Geometry*);

		void Draw(Context* context, Scene* scene);

	private:
		llr::Llr m_llr;

		Size * m_instanceCounterRef = nullptr;
	};

	using PGapi = Gapi*;
}
