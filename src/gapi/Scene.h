#pragma once
#include "api.h"
#include <list>

namespace gapi {
	class Geometry;

	class GAPI_EXPORT Scene final {
	public:
		Scene();

		void AddGeometry(Geometry * geometry);

		void RemoveGeometry(Geometry* geometry);

	private:
		std::list< Geometry* > m_geometries;
	};
}
