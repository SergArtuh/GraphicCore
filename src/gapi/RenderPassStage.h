#pragma once
#include "api.h"

#include <map>
#include <list>

#include "RenderPassConstantInput.h"
#include "RenderPassInstanceArrayInput.h"
#include "RenderPassOutput.h"
#include "Texture2D.h"

namespace gapi {

	class Geometry;

	using RenderPassInputs = std::map<int, PRenderPassConstantInput>;
	using RenderPassInstanceArrayInputs= std::map<int, PRenderPassInstanceArrayInput>;

	using Geometries = std::list<Geometry*>;

	using Textures = std::map<int, PTexture2D>;

	class GAPI_EXPORT RenderPassStage {
		friend class Gapi;
	protected:
		RenderPassStage() = default;
		RenderPassStage(const RenderPassStage&) = default;
		RenderPassStage& operator=(const RenderPassStage&) = default;
	public:
		bool operator==(const RenderPassStage& r);
		
		void SetConstantInput(PRenderPassConstantInput input, I32 location = 0);

		const RenderPassInputs GetRenderPassInputs() const;


		void SetRenderPassOutput(PRenderPassOutput output);

		PRenderPassOutput GetRenderPassOutput() const;


		void SetTexture2D(PTexture2D texture, I32 location = 0);

		const Textures& GetTextures2D();


		void SetGeometryTarget(ERenderPassInputGeometryTarget target);

		ERenderPassInputGeometryTarget  GetGeometryTarget() const;

		void CleanGeomerties();

		void AddGeomerty(Geometry* geometry);

		void RemoveGeomerty(Geometry* geometry);

		const Geometries & GetGeometries();

		void SetRenderPassInstanceArray(PRenderPassInstanceArrayInput, CI32 location = 0);

		RenderPassInstanceArrayInputs GetRenderPassInstanceArrays();

		void SetRenderPassInstanceCount(CSize count);

		Size GetRenderPassInstanceCount() const;


	private:
		RenderPassInputs m_renderPassInputs;

		RenderPassInstanceArrayInputs m_instanceArrays;
		Size m_instanceCount = 0;

		PRenderPassOutput m_renderPassOutput = nullptr;

		ERenderPassInputGeometryTarget m_geometryTarget = ERenderPassInputGeometryTarget::ALL_SCENE;
		Geometries m_geometries;
		Textures m_textures;

	};

	using PRenderPassStage = RenderPassStage*;
}
