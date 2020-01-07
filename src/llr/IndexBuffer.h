#pragma once
#include "api.h"

#include "GL/glew.h"

namespace llr
{
		class  IndexBuffer final
		{
		public:
			IndexBuffer(size_t size);
			~IndexBuffer();

			IndexBuffer(IndexBuffer&);
			IndexBuffer& operator=(IndexBuffer& r);
			

		public:

			void Write(const size_t offset, const size_t size, const void * data);

			void Read(const size_t offset, const size_t size, void * o_data);
			
			GLuint GetId() const {return m_bufferId; }

			bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

		private:
			GLuint m_bufferId = ((GLuint) UNUSED );
			size_t m_size = 0;
			size_t * m_instanceCounterRef = nullptr;
		};
	}
