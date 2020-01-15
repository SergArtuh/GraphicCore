#include "gapi.h"
#include "wnd/window.h"

#include "Scene.h"
#include "Geometry.h"

namespace gapi {
	Gapi::Gapi(wnd::Window& window) : m_llr(window) {
	
	}
	Scene* Gapi::CreateScene()
	{
		return new Scene;
	}
	void Gapi::DeleteScene(Scene * scene)
	{
		if (scene) {
			delete scene;
		}
	}
	Geometry* Gapi::CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes)
	{
		return new Geometry(vertices3f, indexes);
	}
	void Gapi::DeleteGeometry(Geometry* geometry)
	{
		if (geometry) {
			delete geometry;
		}
	}
}