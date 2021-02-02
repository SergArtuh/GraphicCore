#pragma once
#include "api.h"

#include <map>

#include "Texture2D.h"

#include "llr/Framebuffer.h"


namespace gapi {
	class GAPI_EXPORT Framebuffer {
		using Textures = std::map<int, PTexture2D>;
	public:
		Framebuffer() = default;
		Framebuffer(const Framebuffer&) = default;
		Framebuffer& operator=(const Framebuffer&) = default;
	
		llr::Framebuffer & GetFramebufferLlr();
		const llr::Framebuffer & GetFramebufferLlr() const;

		void SetTexture2d(PTexture2D texture, I32 id);

		bool IsValid() const;
	private:
		Textures m_textures;
		llr::Framebuffer m_framebuffer;
	};

	using PFramebuffer = Framebuffer *;
}
