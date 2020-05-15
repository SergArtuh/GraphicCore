#pragma once
#include "api.h"

#include "wnd/IRenderer.h"
#include "llr/VertexArrayBuffer.h"

#include <list>
#include <map>


namespace gapi {
	class Shader;
	class RenderPassStage;
	class Geometry;
	class Camera;

	using RenderPassStages = std::list<RenderPassStage*>;
	using CRenderPassStages = const RenderPassStages;

	class GAPI_EXPORT RenderPass : public wnd::IRenderer{
		friend class Gapi;

	protected:
		RenderPass(Shader * shader);
		RenderPass() = default;
		RenderPass(const RenderPass&) = default;
		RenderPass& operator=(const RenderPass&) = default;
	public:
		bool operator==(const RenderPass& r);
		
		void AddRenderPassStage(RenderPassStage * stage);

		CRenderPassStages & GetRenderPassStage() const;

		RenderPassStages& GetRenderPassStage();

		void SetGeometry(Geometry * geometry);

		void SetCamera(const Camera* geometry);

		void OnRender(wnd::Window& window) override;

		bool IsValid() const;
	private:
		int m_id = UNUSED;
		Shader * m_shader = nullptr;
		RenderPassStages m_stages;
	};
}
