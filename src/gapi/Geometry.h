#pragma once
#include "api.h"

#include "llr/VertexArrayBuffer.h"

#include <vector>


namespace gapi {
	class GAPI_EXPORT Geometry final {
		friend class Gapi;
		friend class Scene;
	private:
		Geometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);
		Geometry() = default;
		Geometry(const Geometry&) = default;
		Geometry& operator=(const Geometry&) = default;

	public:
		bool operator==(const Geometry & r);

		const llr::VertexArrayBuffer GetVertexArrayBuffer() const;

		bool IsValid() const;

		bool IsAddedToScene() const;
	private:

		void SetIsAddedToScene(bool isInScene);

		llr::VertexArrayBuffer m_vao;
		bool m_isAddedScene = false;
	};
}
