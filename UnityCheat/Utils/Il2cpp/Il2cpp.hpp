#pragma once

#include "Il2cpp.h"

CREATE_TYPE(void*, domain_get_assemblies, (void* domain, std::uintptr_t* size));
CREATE_TYPE(void*, il2cpp_domain_get, ());
CREATE_TYPE(char*, il2cpp_field_get_name, (void* field));
CREATE_TYPE(void*, il2cpp_class_get_field_from_name, (void* klass, const char* name));
CREATE_TYPE(std::uintptr_t, il2cpp_field_get_offset, (void* field));
CREATE_TYPE(void*, il2cpp_domain_assembly_open, (void* domain, const char* name));
CREATE_TYPE(void*, il2cpp_class_get_fields, (void* klass, void** iterator));
CREATE_TYPE(void, il2cpp_thread_attach, (void* domain));
CREATE_TYPE(void*, il2cpp_assembly_get_image, (void* assembly));
CREATE_TYPE(void*, il2cpp_class_from_name, (void* image, const char* name_space, const char* klass));
CREATE_TYPE(void*, il2cpp_class_get_method_from_name, (void* klass, const char* name, int param_count));
CREATE_TYPE(void*, il2cpp_method_get_name, (void* method));
CREATE_TYPE(void*, il2cpp_class_get_methods, (void* klass, void** iterator));
CREATE_TYPE(std::uintptr_t, il2cpp_object_new, (void* klass));
CREATE_TYPE(void*, il2cpp_resolve_icall, (const char* method));
CREATE_TYPE(void*, il2cpp_class_get_type, (void* klass));
CREATE_TYPE(void*, il2cpp_type_get_object, (void* klass));

bool TypesAssigned = false;

bool Dumper::think(const char* assembly_name)
{
	for (Assembly& assembly : Assemblies)
	{
		if (assembly.name == assembly_name)
		{
			base_image = assembly.base_image;
			return true;
		}
	}
	if (!TypesAssigned)
	{
		ASSIGN_TYPE(domain_get_assemblies);
		ASSIGN_TYPE(il2cpp_domain_get);
		ASSIGN_TYPE(il2cpp_field_get_name);
		ASSIGN_TYPE(il2cpp_class_get_field_from_name);
		ASSIGN_TYPE(il2cpp_field_get_offset);
		ASSIGN_TYPE(il2cpp_domain_assembly_open);
		ASSIGN_TYPE(il2cpp_class_get_fields);
		ASSIGN_TYPE(il2cpp_thread_attach);
		ASSIGN_TYPE(il2cpp_assembly_get_image);
		ASSIGN_TYPE(il2cpp_class_from_name);
		ASSIGN_TYPE(il2cpp_class_get_method_from_name);
		ASSIGN_TYPE(il2cpp_method_get_name);
		ASSIGN_TYPE(il2cpp_class_get_methods);
		ASSIGN_TYPE(il2cpp_object_new);
		ASSIGN_TYPE(il2cpp_resolve_icall);
		ASSIGN_TYPE(il2cpp_class_get_type);
		ASSIGN_TYPE(il2cpp_type_get_object);
	}
	_il2cpp_thread_attach(_il2cpp_domain_get());
	current_assembly_name = assembly_name;
	base_image = _il2cpp_assembly_get_image(_il2cpp_domain_assembly_open(root_domain, assembly_name));
	Assembly assembly;
	assembly.name = assembly_name;
	assembly.base_image = base_image;
	return true;
}

UINT_PTR Dumper::find_class(const char* class_name, const char* _namespace = "") {

	const auto domain = il2cpp_domain_get();

	UINT_PTR assembly_count{ 0 };
	UINT_PTR* assemblies;
	assemblies = (UINT_PTR*)domain_get_assemblies(domain);

	for (size_t idx{ 0 }; idx < assembly_count; idx++) {
		UINT_PTR* img = (UINT_PTR*)il2cpp_assembly_get_image(assemblies[idx]);
		UINT_PTR kl = (UINT_PTR)_il2cpp_class_from_name((void*)img, _namespace, class_name);
		if (!kl)
			continue;

		return kl;
	}

	return 0;
}

UINT_PTR Dumper::GetObjectType(const char* assembly_name, const char* _namespace, const char* class_name)
{
	Dumper::think(assembly_name);
	auto klass = _il2cpp_class_from_name(base_image, _namespace, class_name);
	auto newobject = (UINT_PTR)_il2cpp_type_get_object(_il2cpp_class_get_type(klass));
	return newobject;
}

UINT_PTR Dumper::GetNewObject(const char* assembly_name, const char* _namespace, const char* class_name)
{
	Dumper::think(assembly_name);
	auto klass = _il2cpp_class_from_name(base_image, _namespace, class_name);
	auto newobject = _il2cpp_object_new(klass);
	return newobject;
}
UINT_PTR Dumper::GetClassOffset(const char* assembly_name, const char* _namespace, const char* class_name) {
	for (Class& klass : Classes) {
		if (klass._namespace == _namespace && klass.class_name == class_name) {
			return klass.Pointer;
		}
	}

	Dumper::think(assembly_name);
	Class klass;
	klass._namespace = _namespace;
	klass.class_name = class_name;
	klass.Pointer = (UINT_PTR)_il2cpp_class_from_name(base_image, _namespace, class_name);
	Classes.push_front(klass);

	if (_namespace != "") {
		printf("[Dumped Class] %s.%s.%s.%s : [0x%X]\n", current_assembly_name, klass._namespace, klass.class_name, klass.Pointer);
	}
	else {
		printf("[Dumped Class] %s.%s.%s : [0x%X]\n", current_assembly_name, klass.class_name, klass.Pointer);
	}

	return klass.Pointer;
}
UINT_PTR Dumper::GetMethodOffset(const char* assembly_name, const char* _namespace, const char* class_name, const char* method_name, int args)
{
	if (assembly_name == "resolve")
	{
		auto ff = (UINT_PTR)il2cpp_resolve_icall(class_name);
		printf("resolving %i", ff);
		return ff;
	}
	for (Method& method : Methods)
	{
		if (method._namespace == _namespace && method.class_name == class_name && method.method_name == method_name)
		{
			return method.Pointer;
		}
	}
	Dumper::think(assembly_name);
	Method method;
	method._namespace = _namespace;
	method.class_name = class_name;
	method.method_name = method_name;
	method.Pointer = (UINT_PTR)((method_info_t*)_il2cpp_class_get_method_from_name(_il2cpp_class_from_name(base_image, _namespace, class_name), method_name, args))->method_ptr - (UINT_PTR)GetModuleHandleA("GameAssembly.dll");
	Methods.push_front(method);
	if (_namespace != "")
	{
		printf("[Dumped Method] %s.%s.%s.%s : [0x%X]\n", current_assembly_name, method._namespace, method.class_name, method.method_name, method.Pointer);
	}
	else
	{
		printf("[Dumped Method] %s.%s.%s : [0x%X]\n", current_assembly_name, method.class_name, method.method_name, method.Pointer);
	}
	return method.Pointer;
}

UINT_PTR Dumper::GetFieldOffet(const char* assembly_name, const char* _namespace, const char* class_name, const char* field_name)
{
	for (Field& field : Fields)
	{
		if (field._namespace == _namespace && field.class_name == class_name && field.field_name == field_name)
		{
			return field.Pointer;
		}
	}
	Dumper::think(assembly_name);
	Field field{ };
	field._namespace = _namespace;
	field.class_name = class_name;
	field.field_name = field_name;
	field.Pointer = _il2cpp_field_get_offset(_il2cpp_class_get_field_from_name(_il2cpp_class_from_name(base_image, _namespace, class_name), field_name));
	Fields.push_front(field);
	if (_namespace != "")
	{
		printf("[Dumped Field] %s.%s.%s.%s : [0x%X]\n", current_assembly_name, field._namespace, field.class_name, field.field_name, field.Pointer);
	}
	else
	{
		printf("[Dumped Field] %s.%s.%s : [0x%X]\n", current_assembly_name, field.class_name, field.field_name, field.Pointer);
	}
	return field.Pointer;
}

#define CLASS(path) klass(STATIC_CRC32(path))

#define FIELD(_assembly, _namespace, _class, _field, name, type) type& name() { \
	__try \
	{ \
		static UINT_PTR var = 0x402402; \
		if (var == 0x402402) var = Dumper::GetFieldOffet(_assembly, _namespace, _class, _field); \
		return *(type*)(this + var); \
	} \
	__except (true) \
	{ \
		printf("%s - Exception Occurred.", __FUNCTION__"\n"); \
	} \
		auto n = nullptr; \
		return reinterpret_cast<type&>(n); \
	}