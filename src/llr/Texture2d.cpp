#include "Texture2d.h"
#include "common/imgio.h"

namespace llr
{
	GLenum TextureFormat2GLenum(ETextureFormat format)
	{
		if (ETextureFormat::RED == format) return GL_RED;
		if (ETextureFormat::RED_INTEGER == format) return GL_RED_INTEGER;

		if (ETextureFormat::RGB == format) return GL_RGB;
		if (ETextureFormat::RGB_INTEGER == format) return GL_RGB_INTEGER;

		if (ETextureFormat::RGBA == format) return GL_RGBA;
		if (ETextureFormat::RGBA_INTEGER == format) return GL_RGBA_INTEGER;
		return -1;
	}


	GLenum TextureSizedFormat2GLenum(ETextureFormat format)
	{
		if (ETextureFormat::RED == format) return GL_R32F;
		if (ETextureFormat::RED_INTEGER == format) return GL_R32UI;

		if (ETextureFormat::RGB == format) return GL_RGB32F;
		if (ETextureFormat::RGB_INTEGER == format) return GL_RGB32UI;

		if (ETextureFormat::RGBA == format) return GL_RGBA32F;
		if (ETextureFormat::RGBA_INTEGER == format) return GL_RGBA32UI;
		return -1;
	}

	UI32 TextureSizedFormatBitPerPixel(ETextureFormat format)
	{
		switch (format)
		{
		case ETextureFormat::RED:
		case ETextureFormat::RED_INTEGER:
			return 1;
		case ETextureFormat::RGB:
		case ETextureFormat::RGB_INTEGER:
			return 3;
		case ETextureFormat::RGBA:
		case ETextureFormat::RGBA_INTEGER:
			return 4;

		default:
			return -1;
		}
	}

	ETextureFormat TextureSizedFormatFromBpp(UI32 bpp, EDataType dataType)
	{
		switch (dataType)
		{
		case EDataType::FLOAT: {
			switch (bpp)
			{
			case 1: return ETextureFormat::RED;
			case 3: return ETextureFormat::RGB;
			case 4: return ETextureFormat::RGBA;
			default: 
				break;
			}
		}	
		case EDataType::UINT: {
			switch (bpp)
			{
			case 1: return ETextureFormat::RED_INTEGER;
			case 3: return ETextureFormat::RGB_INTEGER;
			case 4: return ETextureFormat::RGBA_INTEGER;
			default:
				break;
			}
		}

		default:
			return ETextureFormat::NONE;
		}
	}

	const EDataType TextureFormatDataType(ETextureFormat format)
	{
		switch (format)
		{
		case ETextureFormat::RED:
		case ETextureFormat::RGB:
		case ETextureFormat::RGBA:
			return EDataType::FLOAT;

		case ETextureFormat::RED_INTEGER:	
		case ETextureFormat::RGB_INTEGER:
		case ETextureFormat::RGBA_INTEGER:
			return EDataType::UINT;
			
		default:
			return EDataType::NONE;
		}
	}

	GLenum DataType2GLenum(const EDataType dataType)
	{
		switch (dataType)
		{
		case EDataType::FLOAT:	return GL_FLOAT;
		case EDataType::UINT:	return GL_UNSIGNED_INT;
		default:						break;
		}

		return -1;
	};



	Texture2D::Texture2D(const size_t width, const size_t heigth) : Texture2D(width, heigth, ETextureFormat::RGBA) {
	}

	Texture2D::Texture2D(const size_t width, const size_t height, const ETextureFormat format) {
		Init(width, height, format);
	}

	Texture2D& Texture2D::operator=(const Texture2D& r) {
		m_textureId = r.m_textureId;
		m_referenceCounter = r.m_referenceCounter;
		m_format = r.m_format;
		m_dataType = r.m_dataType;
		m_referenceCounter.Increase();
		return * this;
		
	}

	bool Texture2D::operator==(const Texture2D& r) {
		return m_textureId != UNUSED && r.m_textureId == m_textureId;
	}

	Texture2D::~Texture2D() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_textureId != UNUSED) {
			Deinit();
		}
	}

	void Texture2D::Init(const size_t width, const size_t height, const ETextureFormat format) {
		m_dataType = TextureFormatDataType(format);
		m_format = format;

		if (m_textureId != UNUSED) {
			Deinit();
		}

		glGenTextures(1, &m_textureId);

		glBindTexture(GL_TEXTURE_2D, m_textureId); GL_CHECK


			glTexImage2D(GL_TEXTURE_2D, 0, TextureSizedFormat2GLenum(format), (GLsizei)width, (GLsizei)height, 0, TextureFormat2GLenum(format), DataType2GLenum(m_dataType), nullptr); GL_CHECK


			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); GL_CHECK
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); GL_CHECK

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); GL_CHECK
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); GL_CHECK

			glGenerateMipmap(GL_TEXTURE_2D); GL_CHECK

			glBindTexture(GL_TEXTURE_2D, 0); GL_CHECK
	}

	void Texture2D::Deinit() {
		glDeleteTextures(1, &m_textureId); GL_CHECK
		m_textureId = UNUSED;
	}

	void Texture2D::Write(const size_t xMin, const size_t xMax, size_t yMin, size_t yMax, const void* data) {
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexSubImage2D(GL_TEXTURE_2D, 0, (GLint)xMin, (GLint)yMin, (GLsizei)(xMax - xMin), (GLsizei)(yMax - yMin), TextureFormat2GLenum(m_format), DataType2GLenum(m_dataType), data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Read(const size_t xMin, const size_t xMax, size_t yMin, size_t yMax, void* o_data) {
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glGetTexImage(GL_TEXTURE_2D, 0, TextureFormat2GLenum(m_format), DataType2GLenum(m_dataType), o_data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void Texture2D::Load(const std::string& path) {
		imgio::ImgData imgData = imgio::loadImage(path);
		Init(imgData.Width, imgData.Height, TextureSizedFormatFromBpp(imgData.BPP, EDataType::FLOAT));
		Write(0, imgData.Width, 0, imgData.Height, imgData.PixelData.data());
	}

	void  Texture2D::Save(const std::string& path) {
		if (!IsValid()) {
			return;
		}

		if (m_dataType != EDataType::FLOAT) {
			//TODO: log not supported
		}

		int w, h;
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
		glBindTexture(GL_TEXTURE_2D, 0);

		imgio::ImgData imgData;

		imgData.Path = path;
		imgData.Width = w;
		imgData.Height = h;

		imgData.BPP = TextureSizedFormatBitPerPixel(m_format);

		imgData.PixelData.resize(imgData.BPP * imgData.Width * imgData.Height);

		Read(0, imgData.Width, 0, imgData.Height, imgData.PixelData.data());

		imgio::saveImage(std::move(imgData));

	}

	bool Texture2D::IsValid() const {
		return m_textureId != UNUSED;
	}

	GLuint Texture2D::GetId() const {
		return m_textureId;
	}
}
