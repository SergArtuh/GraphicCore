#include "Texture2D.h"

#include "llr/Texture2d.h"

namespace gapi {
	Texture2D::Texture2D(CSize width, CSize height, ETextureFormat format) : m_texture(width, height, static_cast<llr::ETextureFormat>(format)) {
	}

	void Texture2D::Write(CSize xMin, const CSize xMax, CSize yMin, CSize yMax, const void* data) {
		m_texture.Write(xMin, xMax, yMin, yMax, data);
	}

	void Texture2D::Save(const std::string& path) {
		const std::string pathT = std::string("C:\\tmp\\test") + std::string(path);
		const std::string command = std::string("mkdir ") + pathT;
		system(command.c_str());
	}


	const llr::Texture2D Texture2D::GetTexture2D() const {
		return m_texture;
	}
}