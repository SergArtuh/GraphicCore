#include "api.h"

#include "Common/Vector.h"

extern "C" {
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////VECTORS/////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	Vec2f* CreateVector2f(float *);

	void DeleteVector2f(Vec2f*);

	float GetVector2f(Vec2f* v,UI32 id);

	void SetVector2f(Vec2f* v,UI32 id, float value);



	Vec3f* CreateVector3f(float*);

	void DeleteVector3f(Vec3f*);

	float GetVector3f(Vec3f* v, UI32 id);

	void SetVector3f(Vec3f* v, UI32 id, float value);



	Vec4f* CreateVector4f(float*);

	void DeleteVector4f(Vec4f*);

	float GetVector4f(Vec4f* v, UI32 id);

	void SetVector4f(Vec4f* v, UI32 id, float value);
}