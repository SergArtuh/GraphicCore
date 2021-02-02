#pragma once
#include "api.h"

#include "llr/Texture2d.h"

#include <vector>

namespace gapi {
	class GAPI_EXPORT Texture2D {
		using Data = std::vector<char>;
		using CData = const Data;

		friend class Gapi;
		friend class RenderPassOutput;

	protected:
		Texture2D(CSize width, CSize height, ETextureFormat format = ETextureFormat::RGBA);
		Texture2D() = default;
		Texture2D(const Texture2D&) = default;
		Texture2D& operator=(const Texture2D&) = default;
	public:
		//bool operator==(const RenderPassInput& r);

		void Write(CSize xMin, const CSize xMax, CSize yMin, CSize yMax, const void* data);

		void Save(const std::string & path);

		void Load(const std::string& path);

		const llr::Texture2D GetTexture2DLlr() const;

		bool IsValid() const;
	private:
		llr::Texture2D m_texture;
	};


	using PTexture2D = Texture2D *;
}
