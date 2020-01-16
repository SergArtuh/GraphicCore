#pragma once
#include "api.h"
#include "wnd/IRenderer.h"
#include "llr/Shader.h"
#include "llr/IndexBuffer.h"
#include "llr/VertexBuffer.h"

#include <list>
#include <map>


namespace gapi {
	class Geometry;
	class Context;

	class GAPI_EXPORT RenderPass : public wnd::IRenderer{
		friend class Gapi;
	protected:
		RenderPass(Context* context, llr::Shader& shader);
	public:
		void SetGeometry(const Geometry * geometry);

		void OnRender(wnd::Window& window) override;
	protected:
		const Context * GetContext();
	private:
		llr::Shader m_shader;
		std::map<int, llr::VertexBuffer> m_vertexBuffers;
		llr::IndexBuffer m_indexBuffer;

		const Context * m_context = nullptr;
	};
}
