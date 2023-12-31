struct Ray {
public:
	Vector3 m_Origin;
	Vector3 m_Direction;

	Ray() {
		this->m_Origin = Vector3(0, 0, 0);
		this->m_Direction = Vector3(0, 0, 0);
	}

	Ray(Vector3 origin, Vector3 direction) {
		this->m_Origin = origin;
		this->m_Direction = direction;
	}

	Vector3 ClosestPoint(Vector3 pos) {
		return this->m_Origin + this->m_Direction * (pos - this->m_Origin).Dot(this->m_Direction);
	}
};

namespace Enums
{
    enum BoneHitbox : int
    {
        hhead = 698017942,
        sstomach = -523945340,
        cchest = 827230707,
        lleg = 1286912989,
        rleg = -1963356626,
        rhand = -393310151,
        lhand = -1358607930
    };
	enum LifeState {
		Alive = 0,
		Dead = 1
	};
	enum class Layers
	{
		Terrain = 8388608,
		World = 65536,
		Ragdolls = 512,
		Construction = 2097152,
		ConstructionSocket = 4194304,
		Craters = 1,
		GameTrace = 16384,
		Trigger = 262144,
		VehiclesDetailed = 8192,
		RainFall = 1101070337,
		Deploy = 1235288065,
		DefaultDeployVolumeCheck = 537001984,
		BuildLineOfSightCheck = 2097152,
		ProjectileLineOfSightCheck = 2162688,
		ProjectileLineOfSightCheckTerrain = 10551296,
		MeleeLineOfSightCheck = 2162688,
		EyeLineOfSightCheck = 2162688,
		EntityLineOfSightCheck = 1218519041,
		PlayerBuildings = 18874624,
		PlannerPlacement = 161546496,
		Solid = 1218652417,
		VisCulling = 10551297,
		AltitudeCheck = 1218511105,
		HABGroundEffect = 1218511105,
		AILineOfSight = 1218519297,
		DismountCheck = 1486946561,
		AIPlacement = 278986753,
		WheelRay = 1235321089,
		z = 1503731969,
	};
	enum PlayerFlags : int {
		unused_1 = (1 << 0),
		unused_2 = (1 << 1),
		is_admin = (1 << 2),
		receiving_snapshot = (1 << 3),
		sleeping = (1 << 4),
		spectating = (1 << 5),
		wounded = (1 << 6),
		is_developer = (1 << 7),
		connected = (1 << 8),
		third_person_viewmode = (1 << 10),
		eyes_viewmode = (1 << 11),
		chat_mute = (1 << 12),
		no_sprint = (1 << 13),
		aiming = (1 << 14),
		display_sash = (1 << 15),
		relaxed = (1 << 16),
		safe_zone = (1 << 17),
		server_fall = (1 << 18),
		workbench_1 = (1 << 20),
		workbench_2 = (1 << 21),
		workbench_3 = (1 << 22),
	};
	enum class KeyCode : int {
		None = 0,
		Backspace = 8,
		Delete = 127,
		Tab = 9,
		Clear = 12,
		Return = 13,
		Pause = 19,
		Escapee = 27,
		Space = 32,
		Keypad0 = 256,
		Keypad1 = 257,
		Keypad2 = 258,
		Keypad3 = 259,
		Keypad4 = 260,
		Keypad5 = 261,
		Keypad6 = 262,
		Keypad7 = 263,
		Keypad8 = 264,
		Keypad9 = 265,
		KeypadPeriod = 266,
		KeypadDivide = 267,
		KeypadMultiply = 268,
		KeypadMinus = 269,
		KeypadPlus = 270,
		KeypadEnter = 271,
		KeypadEquals = 272,
		UpArrow = 273,
		DownArrow = 274,
		RightArrow = 275,
		LeftArrow = 276,
		Insert = 277,
		Home = 278,
		End = 279,
		PageUp = 280,
		PageDown = 281,
		F1 = 282,
		F2 = 283,
		F3 = 284,
		F4 = 285,
		F5 = 286,
		F6 = 287,
		F7 = 288,
		F8 = 289,
		F9 = 290,
		F10 = 291,
		F11 = 292,
		F12 = 293,
		F13 = 294,
		F14 = 295,
		F15 = 296,
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,
		Exclaim = 33,
		DoubleQuote = 34,
		Hash = 35,
		Dollar = 36,
		Percent = 37,
		Ampersand = 38,
		Quote = 39,
		LeftParen = 40,
		RightParen = 41,
		Asterisk = 42,
		Plus = 43,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Colon = 58,
		Semicolon = 59,
		Less = 60,
		Equals = 61,
		Greater = 62,
		Question = 63,
		At = 64,
		LeftBracket = 91,
		Backslash = 92,
		RightBracket = 93,
		Caret = 94,
		Underscore = 95,
		BackQuote = 96,
		A = 97,
		B = 98,
		C = 99,
		D = 100,
		E = 101,
		F = 102,
		G = 103,
		H = 104,
		I = 105,
		J = 106,
		K = 107,
		L = 108,
		M = 109,
		N = 110,
		O = 111,
		P = 112,
		Q = 113,
		R = 114,
		S = 115,
		T = 116,
		U = 117,
		V = 118,
		W = 119,
		X = 120,
		Y = 121,
		Z = 122,
		LeftCurlyBracket = 123,
		Pipe = 124,
		RightCurlyBracket = 125,
		Tilde = 126,
		Numlock = 300,
		CapsLock = 301,
		ScrollLock = 302,
		RightShift = 303,
		LeftShift = 304,
		RightControl = 305,
		LeftControl = 306,
		RightAlt = 307,
		LeftAlt = 308,
		LeftCommand = 310,
		LeftApple = 310,
		LeftWindows = 311,
		RightCommand = 309,
		RightApple = 309,
		RightWindows = 312,
		AltGr = 313,
		Help = 315,
		Print = 316,
		SysReq = 317,
		Break = 318,
		Menu = 319,
		Mouse0 = 323,
		Mouse1 = 324,
		Mouse2 = 325,
		Mouse3 = 326,
		Mouse4 = 327,
		Mouse5 = 328,
		Mouse6 = 329
	};
	enum class ModelStateFlags {
		ducked = 1,
		jumped = 2,
		on_ground = 4,
		sleeping = 8,
		sprinting = 16,
		on_ladder = 32,
		flying = 64,
		aiming = 128,
		prone = 256,
		mounted = 512,
		relaxed = 1024,
	};
	enum class ItemCategory : int
	{
		Weapon,
		Construction,
		Items,
		Resources,
		Attire,
		Tool,
		Medical,
		Food
	};
}