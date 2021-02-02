#pragma once
#include "api.h"


#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
	class  ConstantBuffer final {
	public:
		ConstantBuffer();
		ConstantBuffer(Size size);

		ConstantBuffer(const ConstantBuffer&);
		~ConstantBuffer();

		ConstantBuffer& operator=(const ConstantBuffer& r);

		Size GetSize() const;

		void Write(CSize offset, CSize size, const Data data);

		void Read(CSize offset, CSize size, Data o_data);

		GLuint GetId() const { return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

	private:
		ReferenceCounter m_referenceCounter;

		GLuint m_bufferId = ((GLuint)UNUSED);

		Size m_size = 0;
	};
}

