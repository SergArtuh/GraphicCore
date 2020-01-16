#include "RenderPass.h"
#include "Geometry.h"

#include "wnd/window.h"

constexpr const int IB = 0;
constexpr const int VB = 1;



namespace gapi {
	RenderPass::RenderPass(Context* context, llr::Shader& shader) : m_shader(shader), m_context(context)
	{
	}

	void RenderPass::SetGeometry(const Geometry * geometry) {
		m_vertexBuffers.emplace(0, geometry->GetVertexBuffer());
		m_indexBuffer = geometry->GetIndexBuffer();
	}

	void RenderPass::OnRender(wnd::Window& window)
	{
		window.makeContextCurrent();

		for (auto vb : m_vertexBuffers) {
			llr::VertexBuffer vertexBuffer = vb.second;
			
			if (vertexBuffer.IsValid()) {
				int location = vb.first;
				m_shader.SetVertexBuffer(vertexBuffer, location);
			}
		}

		if (m_indexBuffer.IsValid()) {
			m_shader.SetIndexBuffer(m_indexBuffer);
		}

		m_shader.Draw();
	}
	const Context * RenderPass::GetContext()
	{
		return m_context;
	}
}