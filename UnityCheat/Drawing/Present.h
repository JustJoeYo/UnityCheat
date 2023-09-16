class Present
{
public:
	inline static HWND window{ };
	inline static WNDPROC o_wnd_proc;
	inline static ID3D11Device* device{ };
	inline static ID3D11DeviceContext* context{ };
	inline static ID3D11RenderTargetView* main_render_target_view;

	static auto __stdcall WndProc(const HWND hwnd, unsigned int msg, uintptr_t param, long long l_param) ->  long long;
public:
	inline static void* o_present;
	static auto PresentHk(IDXGISwapChain* swap_chain, unsigned int sync, unsigned int flags) -> uintptr_t;
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM param, LPARAM l_param);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM param, LPARAM l_param);

void DirectXShutdown() {
	// destroy everything
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	Present::device->Release();
}

auto __stdcall Present::WndProc(const HWND hwnd, unsigned int msg, uintptr_t param, long long l_param) -> long long
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, param, l_param) || show && !panic)
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (device != NULL && param != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
			ImGui_ImplDX11_CreateDeviceObjects();
		}
		break;

	case WM_DESTROY:
		DirectXShutdown();
		PostQuitMessage(0);
		return 0;
		break;
	}

	return CallWindowProcA(o_wnd_proc, hwnd, msg, param, l_param);
}

void InitImGui(HWND& window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);

	// Load Fonts
	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	// Our state
	ImVec4 clear_color = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.IniFilename = nullptr;
}

bool present_init{ false };
auto Present::PresentHk(IDXGISwapChain* swap_chain, unsigned int sync, unsigned int flags) -> uintptr_t
{
	if (!present_init)
	{
		if (SUCCEEDED(swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&device)))
		{
			device->GetImmediateContext(&context);
			DXGI_SWAP_CHAIN_DESC sd;
			swap_chain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			device->CreateRenderTargetView(pBackBuffer, NULL, &main_render_target_view);
			pBackBuffer->Release();

			o_wnd_proc = (WNDPROC)SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui(window, device, context);

			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(device, context);
		}
		else
			return reinterpret_cast<decltype (&PresentHk)> (o_present) (swap_chain, sync, flags);

		present_init = true;
	}
	context->OMSetRenderTargets(1, &main_render_target_view, nullptr);
	context->RSGetViewports(&vps, &viewport);
	screen_size = { viewport.Width, viewport.Height };
	screen_center = { viewport.Width / 2.0f, viewport.Height / 2.0f };

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		show = !show;
	}

	if (GetAsyncKeyState(VK_END) & 1) {
		show = false;
		panic = true;
	}

	if (!panic) {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawUI();
		//drawing();

		ImGui::EndFrame();

		ImGui::Render();
		context->OMSetRenderTargets(1, &main_render_target_view, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	return reinterpret_cast<decltype (&PresentHk)> (o_present) (swap_chain, sync, flags);
}