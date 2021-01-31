#include "Framebuffer.h"
namespace gapi {
	llr::Framebuffer & Framebuffer::GetFramebufferLlr() {
		return const_cast<llr::Framebuffer &>(this->GetFramebufferLlr());
	}

	const llr::Framebuffer & Framebuffer::GetFramebufferLlr() const {
		return m_framebuffer;
	}

	void Framebuffer::SetTexture2d(PTexture2D texture, I32 id) {
		m_framebuffer.SetTextures2d(texture->GetTexture2DLlr(), id);
		m_textures.emplace(id, texture);
	}

	bool Framebuffer::IsValid() const {
		if(!m_framebuffer.IsValid()) return false;

		for (auto tex : m_textures) {
			if (!tex.second->IsValid()) return false;
		}
		return true;
	}
}