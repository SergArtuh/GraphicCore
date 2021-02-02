#include "RenderPassOutput.h"

namespace gapi {

	bool RenderPassOutput::IsValid() const {
		return m_framebuffer.IsValid();
	}

	void RenderPassOutput::SetTexture2D(const PTexture2D texture2d, I32 id) {
		m_framebuffer.SetTexture2d(texture2d, id);
	}

	const Framebuffer RenderPassOutput::GetFramebuffer() const {
		return m_framebuffer;
	}
}