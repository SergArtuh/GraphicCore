#include "Texture2D.h"

#include "llr/Texture2d.h"

namespace gapi {
	Texture2D::Texture2D(CSize width, CSize height, ETextureFormat format) : m_texture(width, height, static_cast<llr::ETextureFormat>(format)) {
	}

	void Texture2D::Write(CSize xMin, const CSize xMax, CSize yMin, CSize yMax, const void* data) {
		m_texture.Write(xMin, xMax, yMin, yMax, data);
	}

	void Texture2D::Save(const std::string& path) {
		m_texture.Save(path);
	}

	void Texture2D::Load(const std::string& path) {
		m_texture.Load(path);
	}


	const llr::Texture2D Texture2D::GetTexture2DLlr() const {
		return m_texture;
	}

	bool Texture2D::IsValid() const {
		return m_texture.IsValid();
	}
}