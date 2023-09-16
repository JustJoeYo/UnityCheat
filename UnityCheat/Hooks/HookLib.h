class HookLib
{
private:
	uintptr_t m_original{ 0 };
public:

	static auto Awake() -> bool
	{
		if (MH_Initialize() != MH_OK)
			return false;

		return true;
	}

	auto InitializeHook(const char* assembly_name, const char* _namespace, const char* class_name, const char* method_name, void* our_function) -> void
	{
		auto function = reinterpret_cast<void*>(MemoryBase::GameAssembly + Dumper::GetMethodOffset(assembly_name, _namespace, class_name, method_name));
		if (!function)
			return;

		MH_CreateHook((void*)function, our_function, (void**)&m_original);
		MH_EnableHook(function);
	}

	template< typename t>
	auto get_original() -> t
	{
		return reinterpret_cast<t>(m_original);
	}
};

#define CREATE( type, name, args ) inline static HookLib name##hk; static type name args;

