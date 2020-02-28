#pragma once
#include "api.h"

#include "enum.h"

#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
	class  ConstantBuffer final {
	public:
		ConstantBuffer();
		ConstantBuffer(size_t size);

		ConstantBuffer(const ConstantBuffer&);
		~ConstantBuffer();

		ConstantBuffer& operator=(const ConstantBuffer& r);

		size_t GetSize() const;

		void Write(const size_t offset, const size_t size, const void* data);

		void Read(const size_t offset, const size_t size, void* o_data);

		GLuint GetId() const { return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

	private:
		ReferenceCounter m_referenceCounter;

		GLuint m_bufferId = ((GLuint)UNUSED);

		size_t m_size = 0;
	};
}

