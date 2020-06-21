#include "TypeWrapers.h"

Vec2f* CreateVector2f(float* data) {
	if (!data) {
		return new Vec2f;
	}
	constexpr UI32 N = 2;
	return new Vec2f(data);
}

Vec2f* CreateVectorFromNativeData2f(float* ptr) {
	return new Vec2f(ptr, shmem::Use());
}

void DeleteVector2f(Vec2f* v) {
	if (v) {
		delete v;
	}
}

float GetVector2f(Vec2f* v, UI32 id) {
	return (*v)[id];
}

void SetVector2f(Vec2f* v, UI32 id, float value) {
	(*v)[id] = value;
}

Vec3f* CreateVector3f(float*data)
{
	if (!data) {
		return new Vec3f;
	}
	constexpr UI32 N = 3;
	return new Vec3f(data);
}

Vec3f* CreateVectorFromNativeData3f(float* ptr) {
	return new Vec3f(ptr, shmem::Use());
}

void DeleteVector3f(Vec3f*v) {
	if (v) {
		delete v;
	}
}

float GetVector3f(Vec3f* v, UI32 id) {
	return (*v)[id];
}

void SetVector3f(Vec3f* v, UI32 id, float value) {
	(*v)[id] = value;
}

Vec4f* CreateVector4f(float*data) {
	if (!data) {
		return new Vec4f;
	}
	constexpr UI32 N = 4;
	return new Vec4f(data);
}

Vec4f* CreateVectorFromNativeData4f(float * ptr) {
	return new Vec4f(ptr, shmem::Use());
}

void DeleteVector4f(Vec4f* v) {
	if (v) {
		delete v;
	}
}

float GetVector4f(Vec4f* v, UI32 id) {
	return (*v)[id];
}

void SetVector4f(Vec4f* v, UI32 id, float value) {
	(*v)[id] = value;
}




Mat3f* CreateMatrix3f(float* data) {
	if (!data) {
		return new Mat3f;
	}
	constexpr UI32 N = 9;
	return new Mat3f(data, shmem::Use());
}

void DeleteMatrix3f(Mat3f* m) {
	if (m) {
		delete m;
	}
}

float GetMatrix3f(Mat3f* m, UI32 i, UI32 j)
{
	return (*m)[i][j];
}

Vec3f* GetVectorMatrix3f(Mat3f* m, UI32 i)
{
	return m->GetVectorPtr(i);
}

void SetMatrix3f(Mat3f* m, UI32 i, UI32 j, float value) {
	(*m)[i][j] = value;
}




Mat4f* CreateMatrix4f(float * data) {
	if (!data) {
		return new Mat4f;
	}
	constexpr UI32 N = 16;
	return new Mat4f(data);
}

Mat4f* CreateMatrixFromNativeData4f(float* ptr) {
	return new Mat4f(ptr, shmem::Use());
}

void DeleteMatrix4f(Mat4f * m) {
	if (m) {
		delete m;
	}
}

float GetMatrix4f(Mat4f* m, UI32 i, UI32 j)
{
	return (*m)[i][j];
}

Vec4f* GetVectorMatrix4f(Mat4f* m, UI32 i)
{
	return m->GetVectorPtr(i);
}

void SetMatrix4f(Mat4f* m, UI32 i, UI32 j, float value) {
	(*m)[i][j] = value;
}
