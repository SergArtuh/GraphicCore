#pragma once
#include "api.h"
#include "enum.h"

#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
		class  IndexBuffer final
		{
		public:
			IndexBuffer() = default;
			IndexBuffer(size_t size, EDataType type);
			~IndexBuffer();

			IndexBuffer(const IndexBuffer&);
			IndexBuffer& operator=(const IndexBuffer& r);
			

		public:

			void Write(const size_t offset, const size_t size, const void * data);

			void Read(const size_t offset, const size_t size, void * o_data);
			
			GLuint GetId() const {return m_bufferId; }

			size_t GetSize() const;

			EDataType GetDataType() const;

			bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

		private:
			ReferenceCounter m_referenceCounter;

			GLuint m_bufferId = ((GLuint) UNUSED );

			size_t m_size = 0;
			EDataType m_dataType = EDataType::NONE;
		};
	}
