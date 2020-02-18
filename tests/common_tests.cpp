#include<gtest/gtest.h>
#include "Common/Vector.h"
#include "Common/Matrix.h"

TEST(common_tests, Vector) {
	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };


	/////////////////////////////////////////////////////////////////////////
	//////////////////////////Initialization/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	{
		Vec4f v0;
		for (int i = 0; i < v0.size(); ++i) {
			v0[i] = testData0[i];
		}

		for (int i = 0; i < v0.size(); ++i) {
			EXPECT_TRUE(v0[i] == testData0[i]);
		}

		Vec4f v1(v0);

		for (int i = 0; i < v0.size(); ++i) {
			EXPECT_TRUE(v1[i] == testData0[i]);
		}

		std::vector<float> aa = { 5.f, 6.f, 7.f };

		Vec4f v2 = { 1.f, 2.f, 3.f, 4.f };

		for (int i = 0; i < v0.size(); ++i) {
			EXPECT_TRUE(v2[i] == testData0[i]);
		}

		Vec4f v3 = [&v2]() {
			Vec4f vt = v2;
			return vt;
		}();

		for (int i = 0; i < v0.size(); ++i) {
			EXPECT_TRUE(v3[i] == testData0[i]);
		}
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////Dot prodcut/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	{
		Vec4f vd0;
		Vec4f vd1;
		float dot = 0.f;
		for (int i = 0; i < vd0.size(); ++i) {
			vd0[i] = testData0[i];
			vd1[i] = testData1[i];
			dot += testData0[i] * testData1[i];
		}

		EXPECT_EQ(vd0.dot(vd1), dot);
	}


	/////////////////////////////////////////////////////////////////////////
	///////////////////////////////Length/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	{
		Vec4f vl0;
		float len2 = 0.f;
		for (int i = 0; i < vl0.size(); ++i) {
			vl0[i] = testData0[i];
			len2 += testData0[i] * testData0[i];
		}

		const float len = sqrt(len2);

		EXPECT_EQ(vl0.length(), len);
	}

	/////////////////////////////////////////////////////////////////////////
	///////////////////////////////Normalize/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	{
		Vec4f vn0;
		float len2 = 0.f;
		for (int i = 0; i < vn0.size(); ++i) {
			vn0[i] = testData0[i];
			len2 += testData0[i] * testData0[i];
		}

		Vec4f vn1{ vn0 };

		const float len = sqrt(len2);

		for (int i = 0; i < vn0.size(); ++i) {
			vn0[i] /= len;
		}

		vn1.normalize();
		for (int i = 0; i < vn0.size(); ++i) {
			EXPECT_EQ(vn0[i], vn1[i]);
		}
	}
}

TEST(common_tests, Matrix) {
	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };

	const size_t N = 2;


	/////////////////////////////////////////////////////////////////////////
	//////////////////////////Initialization/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Mat2f m0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			m0[i][j] = testData0[j*N + i];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(m0[i][j], testData0[j * N + i]);
		}
	}



	Mat2f m1 = { 1.f, 2.f, 3.f, 4.f };

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(m1[i][j], testData0[j * N + i]);
		}
	}



	Mat2f m2 = m1;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(m2[i][j], testData0[j * N + i]);
		}
	}

	Mat2f m3 = [&m2]() {
		Mat2f mt = m2;
		return mt;
	}();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(m2[i][j], testData0[j * N + i]);
		}
	}
}