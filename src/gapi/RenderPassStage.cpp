#include "RenderPassStage.h"

#include <algorithm>

#include "RenderPassConstantInput.h"

namespace gapi {
	bool RenderPassStage::operator==(const RenderPassStage& r) {
		return m_renderPassInputs == r.m_renderPassInputs;
	}

	void RenderPassStage::SetConstantInput(PRenderPassConstantInput constantInput, I32 location ) {
		m_renderPassInputs.emplace(location, constantInput);
	}

	void RenderPassStage::SetTexture2D(PTexture2D texture, I32 location) {
		m_textures.emplace(location, texture);
	}

	const Textures& RenderPassStage::GetTextures2D() {
		return m_textures;
	}

	const RenderPassInputs RenderPassStage::GetRenderPassInputs() const {
		return m_renderPassInputs;
	}

	void RenderPassStage::SetRenderPassOutput(PRenderPassOutput output) {
		m_renderPassOutput = output;
	}

	PRenderPassOutput RenderPassStage::GetRenderPassOutput() const {
		return m_renderPassOutput;
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

	const Geometries & RenderPassStage::GetGeometries() {
		return m_geometries;
	}
	
	void RenderPassStage::SetRenderPassInstanceArray(PRenderPassInstanceArrayInput instanceArray, CI32 location) {
		m_instanceArrays.emplace(location, instanceArray);
	}

	RenderPassInstanceArrayInputs RenderPassStage::GetRenderPassInstanceArrays() {
		return m_instanceArrays;
	}

	void RenderPassStage::SetRenderPassInstanceCount(CSize count) {
		m_instanceCount = count;
	}

	Size RenderPassStage::GetRenderPassInstanceCount() const {
		return m_instanceCount;
	}
}