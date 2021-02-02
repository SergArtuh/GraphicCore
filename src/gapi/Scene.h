#pragma once
#include "api.h"
#include <list>
#include <map>

namespace gapi {
	class Geometry;
	class Camera;


	class GAPI_EXPORT Scene final {
		friend class Gapi;
	private:
		Scene() = default;
		Scene(const Scene&) = default;
		Scene& operator=(const Scene&) = default;

	public:
		void SetCamera(Camera * );

		[[deprecated]]
		const Camera * GetCamera() const;

		void AddGeometry(Geometry * geometry);

		void RemoveGeometry(Geometry* geometry);

		const std::list< Geometry* >& GetGeometries() const;

	private:
		std::list< Geometry* > m_geometries;
		Camera * m_camera = nullptr;
	};

	using PScene = Scene *;
}
