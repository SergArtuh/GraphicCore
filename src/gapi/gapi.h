#pragma once
#include "api.h"
#include "llr/llr.h"

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
	class RenderPassInstanceArrayInput;
	class RenderPassConstantInput;
	class RenderPassOutput;
	class Camera;
	class Geometry;
	class Texture2D;

	using PContext = Context *;
	using PScene = Scene*;
	using PRenderPass = RenderPass*;
	using PRenderPassStage = RenderPassStage *;
	using PRenderPassInstanceArrayInput = RenderPassInstanceArrayInput*;
	using PRenderPassConstantInput = RenderPassConstantInput*;
	using PRenderPassOutput = RenderPassOutput*;
	using PCamera = Camera*;
	using PGeometry = Geometry*;
	using PTexture2D = Texture2D*;
	

	class GAPI_EXPORT Gapi final {
	public:
		Gapi(wnd::Window & window);
		Gapi(const Gapi & gapi);

		~Gapi();

		PContext CreateContext();

		void DeleteContext(PContext context);

		PScene CreateScene();

		void DeleteScene(PScene );


		PShader CreateShader(const std::list< ShaderSource> & sources);

		void DeleteShader(PShader shader);
		

		PRenderPassConstantInput CreateRenderPassInput(Size size);

		void DeleteRenderPassInput(PRenderPassConstantInput renderPassInput);


		PRenderPassInstanceArrayInput CreateRenderPassInstanceArrayInput(CSize size, EDataType type, CSize count);

		void DeleteRenderPassInstanceArrayInput(PRenderPassInstanceArrayInput instanceArrayInput);


		PRenderPassOutput CreateRenderPassOutput();

		void DeleteRenderPassOutput(PRenderPassOutput renderPassOutput);


		PTexture2D CreateTexture2d(CSize width, CSize height, ETextureFormat format);

		void DeleteTexture2d(PTexture2D texture2d);


		PRenderPassStage CreateRenderPassStage();

		void DeleteRenderPassStage(PRenderPassStage stage);


		PRenderPass CreateRenderPass(PShader shader);

		void DeleteRenderPass(PRenderPass renderPass);

		void AddRenderPassStage(PRenderPass renderPass, PRenderPassStage stage);


		void ContextAddRenderPass(PContext context, PRenderPass renderPass);

		void ContextRemoveRenderPass(PContext context, PRenderPass renderPass);

		[[deprecated]]
		Camera* CreateCamera(float fow, float aspect, float near, float far);

		[[deprecated]]
		void DeleteCamera(PCamera camera);

		PGeometry CreateGeometry(std::vector<float> vertices3f, std::vector<UI32> indexes);

		void DeleteGeometry(PGeometry);

		void Draw(PContext context, PScene scene);

	private:
		llr::Llr m_llr;

		Size * m_instanceCounterRef = nullptr;
	};

	using PGapi = Gapi*;
}
