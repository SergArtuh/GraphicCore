#include "TypeWrapers.h"

Vec2f* CreateVector2f(float* data) {
	if (!data) {
		return new Vec2f;
	}
	constexpr UI32 N = 2;
	return new Vec2f(std::initializer_list<float>(data, data + N));
}

Vec2f* CreateVectorFromNativeData2f(float* ptr) {
	return new Vec2f(ptr);
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
	return new Vec3f(std::initializer_list<float>(data, data + N));
}

Vec3f* CreateVectorFromNativeData3f(float* ptr) {
	return new Vec3f(ptr);
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
	return new Vec4f(std::initializer_list<float>(data, data + N));
}

Vec4f* CreateVectorFromNativeData4f(float * ptr) {
	return new Vec4f(ptr);
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
	return new Mat3f(std::initializer_list<float>(data, data + N));
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
	return new Mat4f(std::initializer_list<float>(data, data + N));
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
