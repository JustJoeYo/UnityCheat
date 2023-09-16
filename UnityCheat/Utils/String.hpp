#pragma once
#include <cstdint>

class IL2CPPString
{
public:
	char zpad[0x10]{ };
	int size{ };
	wchar_t buffer[128 + 1];
public:
	IL2CPPString(const wchar_t* st)
	{
		size = min(wcslen(st), 128);
		for (int idx = 0; idx < size; idx++)
		{
			buffer[idx] = st[idx];
		}
		buffer[size] = 0;
	}
};
class ListDictionary
{
public:
	char pad_0000[0x20];
	class BufferList* keys;
	class BufferList* vals;
};
class BufferList
{
public:
	char pad_0000[0x10];
	int32_t size;
	char pad_0014[0x4];
	void* buffer;
};
namespace misc
{
	bool just_shot = false;
	bool did_reload = false;
	float time_since_last_shot = 0.0f;
	float fixed_time_last_shot = 0.0f;
	float desync_time;
}