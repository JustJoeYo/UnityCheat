class Str {
	char zpad[0x10];
public:
	int size;
	wchar_t str[64 + 1];
	Str(const wchar_t* st) {
		size = min(wcslen((wchar_t*)st), 64);
		for (int i = 0; i < size; i++) {
			str[i] = st[i];
		}
		str[size] = 0;
	}
};
class Color {
public:
	float r;
	float g;
	float b;
	float a;
	Color(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};