#pragma once
#include "api.h"

#include "common/types.h"

#include "GL/glew.h"

#include "ReferenceCounter.h"

#include <map>

namespace llr
{
	class Texture2D;


	class  Framebuffer final : public ReferenceCounter
	{
		using Textures = std::map<int, Texture2D>;
	public:
		Framebuffer() = default;
		~Framebuffer();

		Framebuffer(const Framebuffer&);
		Framebuffer& operator=(const Framebuffer& r);

		static Framebuffer MakeDefault();
			
	public:

		virtual void SetTextures2d(const Texture2D & texture, CI32 location);

		void Clear();

		GLuint GetId() const {return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

	private:
		void Init();
		void Denit();
		void Update();

		ReferenceCounter m_referenceCounter;
		Textures m_textures2d;

		GLuint m_bufferId = ((GLuint) UNUSED );
	};
}
