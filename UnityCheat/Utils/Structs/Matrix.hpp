 struct mat4x4_t
{
	mat4x4_t()
		: m{ { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 } }
	{}

	mat4x4_t(const mat4x4_t&) = default;

	auto transpose() -> mat4x4_t {
		mat4x4_t m;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m.m[i][j] = this->m[j][i];

		return m;
	}

	auto is_empty() -> bool {
		if (!m[3][0] && !m[3][1] && !m[3][2] && !m[2][1] && !m[2][0] && !m[2][2])
			return true;

		return false;
	}

	Vector3 operator*(const Vector3& vec) {
		mat4x4_t m;

		m[3][0] = vec.x;
		m[3][1] = vec.y;
		m[3][2] = vec.z;

		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;


		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;

		auto result = m * (*this);

		return Vector3{ result[3][0], result[3][1], result[3][2] };
	}

	mat4x4_t operator*(const mat4x4_t& _m2) {
		auto _m = *this;

		mat4x4_t out;
		out[0][0] = _m[0][0] * _m2[0][0] + _m[0][1] * _m2[1][0] + _m[0][2] * _m2[2][0] + _m[0][3] * _m2[3][0];
		out[0][1] = _m[0][0] * _m2[0][1] + _m[0][1] * _m2[1][1] + _m[0][2] * _m2[2][1] + _m[0][3] * _m2[3][1];
		out[0][2] = _m[0][0] * _m2[0][2] + _m[0][1] * _m2[1][2] + _m[0][2] * _m2[2][2] + _m[0][3] * _m2[3][2];
		out[0][3] = _m[0][0] * _m2[0][3] + _m[0][1] * _m2[1][3] + _m[0][2] * _m2[2][3] + _m[0][3] * _m2[3][3];
		out[1][0] = _m[1][0] * _m2[0][0] + _m[1][1] * _m2[1][0] + _m[1][2] * _m2[2][0] + _m[1][3] * _m2[3][0];
		out[1][1] = _m[1][0] * _m2[0][1] + _m[1][1] * _m2[1][1] + _m[1][2] * _m2[2][1] + _m[1][3] * _m2[3][1];
		out[1][2] = _m[1][0] * _m2[0][2] + _m[1][1] * _m2[1][2] + _m[1][2] * _m2[2][2] + _m[1][3] * _m2[3][2];
		out[1][3] = _m[1][0] * _m2[0][3] + _m[1][1] * _m2[1][3] + _m[1][2] * _m2[2][3] + _m[1][3] * _m2[3][3];
		out[2][0] = _m[2][0] * _m2[0][0] + _m[2][1] * _m2[1][0] + _m[2][2] * _m2[2][0] + _m[2][3] * _m2[3][0];
		out[2][1] = _m[2][0] * _m2[0][1] + _m[2][1] * _m2[1][1] + _m[2][2] * _m2[2][1] + _m[2][3] * _m2[3][1];
		out[2][2] = _m[2][0] * _m2[0][2] + _m[2][1] * _m2[1][2] + _m[2][2] * _m2[2][2] + _m[2][3] * _m2[3][2];
		out[2][3] = _m[2][0] * _m2[0][3] + _m[2][1] * _m2[1][3] + _m[2][2] * _m2[2][3] + _m[2][3] * _m2[3][3];
		out[3][0] = _m[3][0] * _m2[0][0] + _m[3][1] * _m2[1][0] + _m[3][2] * _m2[2][0] + _m[3][3] * _m2[3][0];
		out[3][1] = _m[3][0] * _m2[0][1] + _m[3][1] * _m2[1][1] + _m[3][2] * _m2[2][1] + _m[3][3] * _m2[3][1];
		out[3][2] = _m[3][0] * _m2[0][2] + _m[3][1] * _m2[1][2] + _m[3][2] * _m2[2][2] + _m[3][3] * _m2[3][2];
		out[3][3] = _m[3][0] * _m2[0][3] + _m[3][1] * _m2[1][3] + _m[3][2] * _m2[2][3] + _m[3][3] * _m2[3][3];

		return out;
	}

	float* operator[](size_t i) { return m[i]; }
	const float* operator[](size_t i) const { return m[i]; }

	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

float insta_travel_check_time = -1.f;

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		}; float m[4][4];
	};
};

class ObjectClass
{
public:
	char pad_0000[48]; //0x0000
	class ComponentListClass* pComponentList; //0x0030
	char pad_0038[40]; //0x0038
	char* pPrefabNameString; //0x0060
	char pad_0068[8]; //0x0068
}; //Size: 0x0070

class CachedPtrClass
{
public:
	char pad_0000[40]; //0x0000
	uint64_t pBaseClass; //0x0028
	class ObjectClass* pObjectClass; //0x0030
	char pad_0038[16]; //0x0038
}; //Size: 0x0048

class ClassPointer
{
public:
	char pad_0000[16]; //0x0000
	char* pEntityClassNameString; //0x0010
}; //Size: 0x0018

class ComponentListClass
{
public:
	char pad_0000[8]; //0x0000
	class ObjectTransformClass* pObjectTransforms; //0x0008
}; //Size: 0x0010

class ObjectTransformClass
{
public:
	char pad_0000[56]; //0x0000
	class ObjectTransformData* pObjectTransformData; //0x0038
	char pad_0040[8]; //0x0040
}; //Size: 0x0048

class ObjectTransformData
{
public:
	char pad_0000[144]; //0x0000
	Vector3 Position; //0x0090
}; //Size: 0x009C

class ContainerInventory
{
public:
	char pad_0000[32]; //0x0000
	uint64_t Item[6]; //0x0020
}; //Size: 0x0050

class StaticCameraClass
{
public:
	char pad_0000[16]; //0x0000
	class StaticCameraPointerOne* PointerOne_; //0x0010
}; //Size: 0x0018

class StaticCameraPointerOne
{
public:
	char pad_0000[48]; //0x0000
	class StaticCameraPointerTwo* PointerTwo_; //0x0030
}; //Size: 0x0038

class StaticCameraPointerTwo
{
public:
	char pad_0000[48]; //0x0000
	class StaticCameraPointerThree* PointerThree_; //0x0030
}; //Size: 0x0038

class StaticCameraPointerThree
{
public:
	char pad_0000[24]; //0x0000
	class StaticCameraPointerFour* PointerFour; //0x0018
}; //Size: 0x0020

class StaticCameraPointerFour
{
public:
	char pad_0000[740]; //0x0000
	Matrix4x4 ViewMatrix; //0x02E4
}; //Size: 0x0324