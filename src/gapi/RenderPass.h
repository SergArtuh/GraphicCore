#pragma once
#include "api.h"
#include "wnd/IRenderer.h"
#include "llr/IndexBuffer.h"
#include "llr/VertexBuffer.h"

#include <list>
#include <map>


namespace gapi {
	class Shader;
	class Geometry;
	class Context;

	class GAPI_EXPORT RenderPass : public wnd::IRenderer{
		friend class Gapi;
	protected:
		RenderPass(Context* context, Shader * shader);
	public:
		bool operator==(const RenderPass& r);

		void SetGeometry(const Geometry * geometry);

		void OnRender(wnd::Window& window) override;
	protected:
		const Context * GetContext();
	private:
		int m_id;
		Shader * m_shader;
		std::map<int, llr::VertexBuffer> m_vertexBuffers;
		llr::IndexBuffer m_indexBuffer;

		const Context * m_context = nullptr;
	};
}
