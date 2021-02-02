#pragma once
#include "api.h"
#include "llr/Framebuffer.h"
#include "Texture2D.h"
#include "Framebuffer.h"

#include <vector>

namespace gapi {

	class GAPI_EXPORT RenderPassOutput {
		friend class Gapi;
	protected:
		RenderPassOutput() = default;
		RenderPassOutput(const RenderPassOutput&) = default;
		RenderPassOutput& operator=(const RenderPassOutput&) = default;
	public:

		bool IsValid() const;

		void SetTexture2D(const PTexture2D texture2d, I32 id = 0);

		const Framebuffer GetFramebuffer() const;

	private:
		Framebuffer m_framebuffer;
	};



	using PRenderPassOutput = RenderPassOutput * ;
}
