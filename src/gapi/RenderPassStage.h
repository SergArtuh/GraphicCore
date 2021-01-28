#pragma once
#include "api.h"

#include <map>
#include <list>

#include "enum.h"
#include "RenderPassInput.h"
#include "RenderPassOutput.h"
#include "Texture2D.h"

namespace gapi {

	class Geometry;

	using RenderPassInputs = std::map<int, RenderPassInput*>;
	using CRenderPassInputs = const RenderPassInputs;

	using Geometries = std::list<Geometry*>;
	using CGeometries = const Geometries;

	using Textures = std::map<int, PTexture2D>;
	using CTextures = const Textures;

	class GAPI_EXPORT RenderPassStage {
		friend class Gapi;
	protected:
		RenderPassStage() = default;
		RenderPassStage(const RenderPassStage&) = default;
		RenderPassStage& operator=(const RenderPassStage&) = default;
	public:
		bool operator==(const RenderPassStage& r);
		
		void SetInput(PRenderPassInput input, I32 location = 0);

		CRenderPassInputs GetRenderPassInputs() const;


		void SetRenderPassOutput(PRenderPassOutput output);

		PRenderPassOutput GetRenderPassOutput() const;


		void SetTexture2D(PTexture2D texture, I32 location = 0);

		CTextures& GetTextures2D();


		void SetGeometryTarget(ERenderPassInputGeometryTarget target);

		ERenderPassInputGeometryTarget  GetGeometryTarget() const;

		void CleanGeomerties();

		void AddGeomerty(Geometry* geometry);

		void RemoveGeomerty(Geometry* geometry);

		CGeometries & GetGeometries();


	private:
		RenderPassInputs m_renderPassInputs;
		PRenderPassOutput m_renderPassOutput = nullptr;

		ERenderPassInputGeometryTarget m_geometryTarget = ERenderPassInputGeometryTarget::ALL_SCENE;
		Geometries m_geometries;
		Textures m_textures;

	};

	using PRenderPassStage = RenderPassStage*;
}
