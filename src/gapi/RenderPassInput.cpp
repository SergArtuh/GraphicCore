#include "RenderPassInput.h"

namespace gapi {
	RenderPassInput::RenderPassInput(size_t size) : m_constantBuffer(size) {
		m_data.resize(size);
	}
	const llr::ConstantBuffer RenderPassInput::GetConstantBuffer() const {
		return m_constantBuffer;
	}

	RenderPassInput::Data & RenderPassInput::GetData() {
		return m_data;
	}

	RenderPassInput::CData & RenderPassInput::GetData() const {
		return m_data;
	}

	void RenderPassInput::Update() {
		m_constantBuffer.Write(0, m_data.size(), m_data.data());
	}

	bool RenderPassInput::IsValid() const {
		return m_constantBuffer.IsValid();
	}
}