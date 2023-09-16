#pragma once

class Character {
public:
	FIELD("Brainwash.FKF.Runtime", "", "Character", "m_predatorVision", m_predatorVision, bool);
};

class BobEffect {
public:
	FIELD("Brainwash.FKF.Runtime", "", "BobEffect", "bobbingSpeed", bobbingSpeed, Vector2);
	FIELD("Brainwash.FKF.Runtime", "", "BobEffect", "bobbingAmount", bobbingAmount, Vector2);
};

class WeaponView {
public:
	FIELD("Brainwash.FKF.Runtime", "Brainwash.FKF.Weapons", "WeaponView", "spread", spread, float);
	FIELD("Brainwash.FKF.Runtime", "Brainwash.FKF.Weapons", "WeaponView", "maxSpread", maxSpread, float);
	FIELD("Brainwash.FKF.Runtime", "Brainwash.FKF.Weapons", "WeaponView", "spreadPercent", spreadPercent, float);
};

class CharacterMovementController {
public:

};

mat4x4_t viewMatrix = {};
uintptr_t camera = {};
inline StaticCameraClass* StaticCamera = 0;
inline Matrix4x4* GlobalCurrentViewMatrix = nullptr;
class Camera
{
public:
	static uintptr_t Get_Camera()
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;

		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_main");
			}

			typedef uintptr_t Method();
			auto pCamera = ((Method*)(MemoryBase::GameAssembly + var))();

			return pCamera;
		}
		__except (true)
		{
			printf("%s - Exception occurred, __FUNCTION__");
		}
		return 0;
	}
	class ViewMatrix
	{
	public:
		static auto getViewMatrix() -> mat4x4_t
		{
			if (!camera)
			{
				camera = Camera::Get_Camera();
				return mat4x4_t();
			}

			auto camera_ = *reinterpret_cast<std::uintptr_t*>(camera + 0x10);
			if (!camera_) {
				camera = Camera::Get_Camera();
				return mat4x4_t();
			}

			auto matrix = *reinterpret_cast<mat4x4_t*>(camera_ + 0x2e4);
			if (!matrix.m) {
				camera = Camera::Get_Camera();
				return mat4x4_t();
			}
			return matrix;
		}
	};
	class WorldToScreen
	{
	public:
		static bool WorldToScreens(const Vector3& EntityPos, Vector2& ScreenPos)
		{
			auto matrixs = Camera::ViewMatrix::getViewMatrix();

			if (!matrixs.m) {
				return 0;
			}

			const auto matrix = matrixs.transpose();

			Vector3 translation = { matrix[3][0], matrix[3][1], matrix[3][2] };
			Vector3 up = { matrix[1][0], matrix[1][1], matrix[1][2] };
			Vector3 right = { matrix[0][0], matrix[0][1], matrix[0][2] };

			auto w = translation.dot_product(EntityPos) + matrix[3][3];

			if (w < 0.1f)
				return false;

			auto x = right.dot_product(EntityPos) + matrix[0][3];
			auto y = up.dot_product(EntityPos) + matrix[1][3];

			ScreenPos =
			{
				screen_center.x * (1.f + x / w),
				screen_center.y * (1.f - y / w)
			};

			return true;
		}
	};
};