#pragma once
#include "api.h"
#include "enum.h"

#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
	class Texture2D;


	class  Framebuffer final : public ReferenceCounter
	{
	public:
		Framebuffer() = default;
		Framebuffer(CSize width, const CSize heigth);
		~Framebuffer();

		Framebuffer(const Framebuffer&);
		Framebuffer& operator=(const Framebuffer& r);
			
	public:

		virtual void SetTextures2d(const Texture2D & texture, const int location);

		GLuint GetId() const {return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

	private:
		ReferenceCounter m_referenceCounter;

		GLuint m_bufferId = ((GLuint) UNUSED );

		Size m_width = 0;
		Size m_heigth = 0;
	};
}
