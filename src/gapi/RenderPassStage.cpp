#include "RenderPassStage.h"

#include <algorithm>

#include "RenderPassInput.h"

namespace gapi {
	bool RenderPassStage::operator==(const RenderPassStage& r) {
		return m_renderPassInputs == r.m_renderPassInputs;
	}

	void RenderPassStage::SetInput(PRenderPassInput input, I32 location ) {
		m_renderPassInputs.emplace(location, input);
	}

	void RenderPassStage::SetTexture2D(PTexture2D texture, I32 location) {
		m_textures.emplace(location, texture);
	}

	CTextures& RenderPassStage::GetTextures2D() {
		return m_textures;
	}

	CRenderPassInputs RenderPassStage::GetRenderPassInputs() const {
		return m_renderPassInputs;
	}

	void RenderPassStage::SetGeometryTarget(ERenderPassInputGeometryTarget target) {
		m_geometryTarget = target;
	}

	ERenderPassInputGeometryTarget RenderPassStage::GetGeometryTarget() const {
		return m_geometryTarget;
	}

	void RenderPassStage::CleanGeomerties() {
		m_geometries.clear();
	}

	void RenderPassStage::AddGeomerty(Geometry* geometry) {
		m_geometries.push_back(geometry);
	}

	void RenderPassStage::RemoveGeomerty(Geometry* geometry) {
		m_geometries.erase(std::remove_if(m_geometries.begin(), m_geometries.end(), [geometry](auto g) {return g == geometry; }), m_geometries.end());
	}

	CGeometries & RenderPassStage::GetGeometries() {
		return m_geometries;
	}
}