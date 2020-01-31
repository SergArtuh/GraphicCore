#include "Scene.h"
#include "Geometry.h"

#include <algorithm>

namespace gapi {
	void Scene::AddGeometry(Geometry* geometry)
	{
		if (!(geometry && geometry->IsValid())) {
			return;
		}
		m_geometries.push_back(geometry);
	}

	void Scene::RemoveGeometry(Geometry* geometry)
	{
		if (!(geometry && geometry->IsValid())) {
			return;
		}

		auto finded = std::find_if(m_geometries.begin(), m_geometries.end(), [geometry](auto g) {
			return *geometry == *g;
		} );
		if (finded != m_geometries.end()) {
			m_geometries.remove(geometry);
		}
	}

	const std::list<Geometry*>& Scene::GetGeometries() const
	{
		return m_geometries;
	}
}