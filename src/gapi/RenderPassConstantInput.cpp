#include "RenderPassConstantInput.h"

namespace gapi {
	RenderPassConstantInput::RenderPassConstantInput(size_t size) : m_constantBuffer(size) {
		m_data.resize(size);
	}
	const llr::ConstantBuffer RenderPassConstantInput::GetConstantBuffer() const {
		return m_constantBuffer;
	}

	RenderPassConstantInput::Data & RenderPassConstantInput::GetData() {
		return m_data;
	}

	const RenderPassConstantInput::Data & RenderPassConstantInput::GetData() const {
		return m_data;
	}

	void RenderPassConstantInput::Update() {
		m_constantBuffer.Write(0, m_data.size(), m_data.data());
	}

	bool RenderPassConstantInput::IsValid() const {
		return m_constantBuffer.IsValid();
	}
}