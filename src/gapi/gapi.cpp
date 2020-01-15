#include "gapi.h"
#include "wnd/window.h"

#include "Scene.h"

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
}