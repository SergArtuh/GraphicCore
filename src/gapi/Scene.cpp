#include "Scene.h"

#include <algorithm>

namespace gapi {
	Scene::Scene()  {
	}
	void Scene::AddGeometry(Geometry* geometry)
	{
		if (!geometry) {
			return;
		}
		m_geometries.push_back(geometry);
	}

	void Scene::RemoveGeometry(Geometry* geometry)
	{
		if (!geometry) {
			return;
		}

		auto finded = std::find(m_geometries.begin(), m_geometries.end(), geometry);
		if (finded != m_geometries.end()) {
			m_geometries.remove(geometry);
		}
	}

	const std::list<Geometry*>& Scene::GetGeometries() const
	{
		return m_geometries;
	}

	void Scene::Draw()
	{
	}
}