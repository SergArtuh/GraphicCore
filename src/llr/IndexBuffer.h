#pragma once
#include "api.h"

#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
		class  IndexBuffer final : public ReferenceCounter
		{
		public:
			IndexBuffer() = default;
			IndexBuffer(Size size, EDataType type);
			~IndexBuffer();

			IndexBuffer(const IndexBuffer&);
			IndexBuffer& operator=(const IndexBuffer& r);
			
		public:

			void Write(CSize offset, CSize size, const Data data);

			void Read(CSize offset, CSize size, Data o_data);
			
			GLuint GetId() const {return m_bufferId; }

			Size GetSize() const;

			EDataType GetDataType() const;

			bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

		private:
			ReferenceCounter m_referenceCounter;

			GLuint m_bufferId = ((GLuint) UNUSED );

			Size m_size = 0;
			EDataType m_dataType = EDataType::NONE;
		};
	}
