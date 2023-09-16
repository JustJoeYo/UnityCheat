class Quaternion {
public:
	float x, y, z, w;

	Quaternion() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}
	Quaternion(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion operator*(Quaternion rhs) {
		return Quaternion(
			this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y,
			this->w * rhs.y + this->y * rhs.w + this->z * rhs.x - this->x * rhs.z,
			this->w * rhs.z + this->z * rhs.w + this->x * rhs.y - this->y * rhs.x,
			this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z
		);
	}

	float Dot(Quaternion b) {
		return x * x + y * y + z * z + w * w;
	}
	static Vector3 QuaternionMultiply(Vector3 Point, Quaternion Quaternion) {
		float Num = Quaternion.x * 2.f;
		float Num2 = Quaternion.y * 2.f;
		float Num3 = Quaternion.z * 2.f;
		float Num4 = Quaternion.x * Num;
		float Num5 = Quaternion.y * Num2;
		float Num6 = Quaternion.z * Num3;
		float Num7 = Quaternion.x * Num2;
		float Num8 = Quaternion.x * Num3;
		float Num9 = Quaternion.y * Num3;
		float Num10 = Quaternion.w * Num;
		float Num11 = Quaternion.w * Num2;
		float Num12 = Quaternion.w * Num3;
		Vector3 Result;
		Result.x = (1.f - (Num5 + Num6)) * Point.x + (Num7 - Num12) * Point.y + (Num8 + Num11) * Point.z;
		Result.y = (Num7 + Num12) * Point.x + (1.f - (Num4 + Num6)) * Point.y + (Num9 - Num10) * Point.z;
		Result.z = (Num8 - Num11) * Point.x + (Num9 + Num10) * Point.y + (1.f - (Num4 + Num5)) * Point.z;
		return Result;
	}
	Vector3 operator*(Vector3 point) {
		float num = this->x * 2.f;
		float num2 = this->y * 2.f;
		float num3 = this->z * 2.f;
		float num4 = this->x * num;
		float num5 = this->y * num2;
		float num6 = this->z * num3;
		float num7 = this->x * num2;
		float num8 = this->x * num3;
		float num9 = this->y * num3;
		float num10 = this->w * num;
		float num11 = this->w * num2;
		float num12 = this->w * num3;
		Vector3 result;
		result.x = (1.f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1.f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.f - (num4 + num5)) * point.z;
		return result;
	}
};