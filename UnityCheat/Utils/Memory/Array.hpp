template<typename T = void*>
class Array {
public:
	uint32_t ArraySize() {
		__try {
			return *reinterpret_cast<uint32_t*>(this + 0x18);
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
	T GetArray(int idx) {
		__try {
			return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
	void AddArray(int idx, T value) {
		__try {
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
};
template<typename type>
class List
{
public:
	type get(std::uint32_t idx)
	{
		const auto internal_list = reinterpret_cast<std::uintptr_t>(this + 0x20);
		return *reinterpret_cast<type*>(internal_list + idx * sizeof(type));
	}

	type value(std::uint32_t idx)
	{
		const auto list = *reinterpret_cast<std::uintptr_t*>(this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<type*>(internal_list + idx * sizeof(type));
	}

	auto size() -> const std::uint32_t { return *reinterpret_cast<std::uint32_t*>(this + 0x18); }
};
