#pragma once
#include "api.h"

#include "RenderPassInput.h"

#include "wnd/IRenderer.h"
#include "llr/IndexBuffer.h"
#include "llr/VertexBuffer.h"

#include <list>
#include <map>


namespace gapi {
	class Shader;
	class Geometry;

	class GAPI_EXPORT RenderPass : public wnd::IRenderer{
		friend class Gapi;
	protected:
		RenderPass(Shader * shader);
		RenderPass() = default;
		RenderPass(const RenderPass&) = default;
		RenderPass& operator=(const RenderPass&) = default;
	public:
		bool operator==(const RenderPass& r);
		
		void SetInput(RenderPassInput * input, int location = 0);

		void SetGeometry(const Geometry * geometry);

		void OnRender(wnd::Window& window) override;

		bool IsValid() const;
	private:
		int m_id = UNUSED;
		Shader * m_shader = nullptr;
		std::map<int, llr::VertexBuffer> m_vertexBuffers;
		llr::IndexBuffer m_indexBuffer;
	};
}
