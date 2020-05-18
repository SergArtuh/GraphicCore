#pragma once

#include "GL/glew.h"

#include "api.h"
#include "enum.h"

#include "ReferenceCounter.h"

namespace llr
{
	class  Texture2D final
	{
		public:

			Texture2D(const size_t width, const size_t heigth);

			Texture2D(const size_t width, const size_t heigth, const ETextureFormat usageFormat);

			Texture2D() = default;

			Texture2D(const Texture2D&) = default;

			~Texture2D();

			Texture2D& operator=(const Texture2D& r);

			bool operator==(const Texture2D& r);

			void Write(const size_t xMin, const size_t xMax, size_t yMin, size_t yMax, const void * data);

			void Read(const size_t xMin, const size_t xMax, size_t yMin, size_t yMax, void * o_data);

			bool IsValid() const;

			GLuint GetId() const;
		private:

			ReferenceCounter m_referenceCounter;

			ETextureFormat m_format = ETextureFormat::NONE;
			EDataType m_dataType = EDataType::NONE;

			GLuint m_textureId = (GLuint)UNUSED;
		};
	}
