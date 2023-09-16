#define ProcAddr(func) GetProcAddress((HMODULE)MemoryBase::GameAssembly, func)

template<typename T, typename... Args>
inline T Call(const char* func, Args... args) {
	return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
}
class String {
public:
	char pad_0000[0x10];
	int len;
	wchar_t buffer[0];

	static String* New(const char* str) {
		return Call<String*, const char*>(("il2cpp_string_new"), str);
	}
};

inline static UINT_PTR GetType(const char* qualified_name)
{
	static auto off = MemoryBase::GameAssembly + Dumper::GetMethodOffset("mscorlib", "System", "Type", "GetType", 1);
	return reinterpret_cast<UINT_PTR(__cdecl*)(String*)>(off)(String::New(qualified_name));
}

inline UINT_PTR GetComponent(UINT_PTR type, UINT_PTR pointer) {
	typedef UINT_PTR getComp(UINT_PTR, UINT_PTR);
	return ((getComp*)(MemoryBase::GameAssembly + Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Component", "GetComponent", 1)))(pointer, type);
}

inline UINT_PTR GetGameObjectComponent(UINT_PTR type, UINT_PTR pointer) {
	typedef UINT_PTR getComp(UINT_PTR, UINT_PTR);
	return ((getComp*)(MemoryBase::GameAssembly + Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponent", 1)))(pointer, type);
}

inline static UINT_PTR GUIDToObject(String* guid) {
	typedef UINT_PTR GUIDToObject(String*);
	return ((GUIDToObject*)(MemoryBase::GameAssembly + Dumper::GetMethodOffset("Assembly-CSharp", "", "GameManifest", "GUIDToObject", 1)))(guid);
}
inline UINT_PTR GetClassObject(UINT_PTR pointer) {
	String* guid = *reinterpret_cast<String**>(pointer + 0x10);
	UINT_PTR _cachedObject = GUIDToObject(guid);
	return _cachedObject;
}
