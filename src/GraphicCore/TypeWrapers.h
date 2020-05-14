#include "api.h"

#include "Common/Vector.h"
#include "Common/Matrix.h"

extern "C" {
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////VECTORS/////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	Vec2f* CreateVector2f(float *);

	Vec2f* CreateVectorFromNativeData2f(float* ptr);

	void DeleteVector2f(Vec2f*);

	float GetVector2f(Vec2f* v,UI32 id);

	void SetVector2f(Vec2f* v,UI32 id, float value);



	Vec3f* CreateVector3f(float*);

	Vec3f* CreateVectorFromNativeData3f(float* ptr);

	void DeleteVector3f(Vec3f*);

	float GetVector3f(Vec3f* v, UI32 id);

	void SetVector3f(Vec3f* v, UI32 id, float value);



	Vec4f* CreateVector4f(float*);

	Vec4f* CreateVectorFromNativeData4f(float* ptr);

	void DeleteVector4f(Vec4f*);

	float GetVector4f(Vec4f* v, UI32 id);

	void SetVector4f(Vec4f* v, UI32 id, float value);


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////Matrices/////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	Mat3f* CreateMatrix3f(float* data);

	void DeleteMatrix3f(Mat3f* m);

	float GetMatrix3f(Mat3f* m, UI32 i, UI32 j);

	Vec3f* GetVectorMatrix3f(Mat3f* m, UI32 i);

	void SetMatrix3f(Mat3f* m, UI32 i, UI32 j, float value);



	Mat4f * CreateMatrix4f(float*);

	Mat4f * CreateMatrixFromNativeData4f(float* ptr);

	void DeleteMatrix4f(Mat4f*);

	float GetMatrix4f(Mat4f* v, UI32 i, UI32);

	Vec4f * GetVectorMatrix4f(Mat4f* v, UI32 i);

	void SetMatrix4f(Mat4f* v, UI32 i, UI32 j, float value);
}