#include "TypeWrapers.h"

Vec2f* CreateVector2f(float* data) {
	if (!data) {
		return new Vec2f;
	}
	constexpr UI32 N = 2;
	return new Vec2f(std::initializer_list<float>(data, data + N));
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

Vec4f* CreateVector4f(float*data)
{
	if (!data) {
		return new Vec4f;
	}
	constexpr UI32 N = 4;
	return new Vec4f(std::initializer_list<float>(data, data + N));
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
