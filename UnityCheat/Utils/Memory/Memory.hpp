#pragma once

inline static UINT vps = 1;
Vector2 screen_size = { 0, 0 };
Vector2 screen_center = { 0, 0 };
D3D11_VIEWPORT viewport;

namespace MemoryBase
{
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	inline uintptr_t GameAssembly = 0;
}



float Distance_3D(Vector3 a, Vector3 b) {
	return sqrtf(powf((a.x - b.x), 2) + powf((a.y - b.y), 2) + powf((a.z - b.z), 2));
}
double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
	double pitch = (Vector3::my_atan2(height, DepthPlayerTarget));
	double BulletVelocityXY = velocity * Vector3::my_cos(pitch);
	double Time = DepthPlayerTarget / BulletVelocityXY;
	double TotalVerticalDrop = (0.4905f * gravity * Time * Time);
	return TotalVerticalDrop * 10;
}
void Predictions(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity) {
	float Dist = Distance_3D(target, local);
	float BulletTime = Dist / bulletspeed;
	Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;
	Vector3 PredictVel = vel * BulletTime;
	target += PredictVel;
	double height = target.y - local.y;
	Vector3 dir = target - local;
	float DepthPlayerTarget = Vector3::my_sqrt((dir.x * dir.x) + (dir.z * dir.z));
	float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity);
	target.y += drop;
}