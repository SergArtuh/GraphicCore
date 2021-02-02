#include "RenderPassInstanceArrayInput.h"

namespace gapi {
	RenderPassInstanceArrayInput::RenderPassInstanceArrayInput(CSize size, EDataType type, CSize count) : m_vertexBuffer(size, type, count, true) {}

	bool RenderPassInstanceArrayInput::operator==(const RenderPassInstanceArrayInput& r) {
		return m_vertexBuffer.GetId() != UNUSED && m_vertexBuffer.GetId() == r.m_vertexBuffer.GetId();
	}

	const llr::VertexBuffer RenderPassInstanceArrayInput::GetVertexBufferLlr() const {
		return m_vertexBuffer;
	}
	
	void RenderPassInstanceArrayInput::Write(CSize offset, CSize size, const Data data) {
		m_vertexBuffer.Write(offset, size, data);
	}

	bool RenderPassInstanceArrayInput::IsValid() const {
		return m_vertexBuffer.IsValid();
	}
}