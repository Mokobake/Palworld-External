#pragma once

void GetProcessInfo(const wchar_t* FileName)
{
    HANDLE PSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 Process = {};
    Process.dwSize = sizeof(Process);

    while (Process32Next(PSnapshot, &Process))
    {
        if (!_wcsicmp(FileName, Process.szExeFile))
        {
            ProcessID = Process.th32ProcessID;
            ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
            break;
        }
    }

    HANDLE MSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    MODULEENTRY32 Module;
    Module.dwSize = sizeof(Module);

    while (Module32Next(MSnapshot, &Module))
    {
        if (!_wcsicmp(FileName, Module.szModule))
        {
            ProcessBaseAddress = (uintptr_t)Module.modBaseAddr;
            break;
        }
    }
}

uintptr_t PatternScan(const char* sig, const char* mask)
{
    auto buffer = std::make_unique<std::array<uint8_t, 0x100000>>();
    auto data = buffer.get()->data();

    for (uintptr_t i = 0u; i < (2u << 25u); ++i)
    {
        ReadProcessMemory(ProcessHandle, LPVOID(ProcessBaseAddress + i * 0x100000), data, 0x100000, 0);

        if (!data)
            return 0;

        for (uintptr_t j = 0; j < 0x100000u; ++j)
        {
            if ([](uint8_t const* data, uint8_t const* sig, char const* mask)
                {
                    for (; *mask; ++mask, ++data, ++sig)
                    {
                        if (*mask == 'x' && *data != *sig) return false;
                    }
                    return (*mask) == 0;
                }(data + j, (uint8_t*)sig, mask))
            {
                uintptr_t result = ProcessBaseAddress + i * 0x100000 + j;
                uint32_t rel = 0;

                ReadProcessMemory(ProcessHandle, LPVOID(result + 3), &rel, sizeof(uint32_t), 0);

                if (!rel)
                    return 0;

                return result + rel + 7;
            }
        }
    }

    return 0;
}

template<typename T>
void write(uintptr_t Address, T Buffer)
{
    WriteProcessMemory(ProcessHandle, LPVOID(Address), &Buffer, sizeof(Buffer), NULL);
}

template<typename T>
T read(uintptr_t Address)
{
    T Buffer;
    ReadProcessMemory(ProcessHandle, LPVOID(Address), &Buffer, sizeof(Buffer), NULL);
    return Buffer;
}

void read(uintptr_t Address, void* Buffer, size_t Size)
{
    ReadProcessMemory(ProcessHandle, LPVOID(Address), &Buffer, sizeof(Size), NULL);
}

void Error(std::string ErrorInfo)
{
    system("cls");
    std::cout << "\n  Error: " << ErrorInfo << ".\n  ";
    system("pause");
}

void Shutdown()
{
    TriBuf->Release();
    D3dDevice->Release();
    p_Object->Release();

    DestroyWindow(Overlay);
    UnregisterClass(L"Palworld Cheat Overlay", NULL);
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }

    switch (msg)
    {
    case WM_DESTROY:
        Shutdown();
        PostQuitMessage(0);
        exit(1);
        break;
    case WM_SIZE:
        if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            d3dpp.BackBufferWidth = LOWORD(lParam);
            d3dpp.BackBufferHeight = HIWORD(lParam);
            HRESULT hr = D3dDevice->Reset(&d3dpp);
            if (hr == D3DERR_INVALIDCALL)
                IM_ASSERT(0);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return 0;
}

void SetWindowToTarget()
{
    while (true)
    {
        if (ProcessWindow)
        {
            ZeroMemory(&ProcessWindowRect, sizeof(ProcessWindowRect));
            GetWindowRect(ProcessWindow, &ProcessWindowRect);
            ProcessWindowWidth = ProcessWindowRect.right - ProcessWindowRect.left;
            ProcessWindowHeight = ProcessWindowRect.bottom - ProcessWindowRect.top;
            DWORD dwStyle = GetWindowLong(ProcessWindow, GWL_STYLE);

            if (dwStyle & WS_BORDER)
            {
                ProcessWindowRect.top += 32;
                ProcessWindowHeight -= 39;
            }
            ProcessWindowCenterX = ProcessWindowWidth / 2;
            ProcessWindowCenterY = ProcessWindowHeight / 2;
            MoveWindow(Overlay, ProcessWindowRect.left, ProcessWindowRect.top, ProcessWindowWidth, ProcessWindowHeight, true);
        }
        else
        {
            exit(2);
        }
    }
}

void CreateOverlay()
{
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SetWindowToTarget, NULL, NULL, NULL);

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpszClassName = L"Palworld Cheat Overlay";
    wc.lpfnWndProc = WndProc;
    RegisterClassEx(&wc);

    if (ProcessWindow)
    {
        GetClientRect(ProcessWindow, &ProcessWindowRect);
        POINT xy;
        ClientToScreen(ProcessWindow, &xy);
        ProcessWindowRect.left = xy.x;
        ProcessWindowRect.top = xy.y;

        ProcessWindowWidth = ProcessWindowRect.right;
        ProcessWindowHeight = ProcessWindowRect.bottom;
    }
    else
    {
        exit(3);
    }

    Overlay = CreateWindowEx(NULL, L"Palworld Cheat Overlay", L"Overlay", WS_POPUP | WS_VISIBLE, NULL, NULL, ProcessWindowWidth, ProcessWindowHeight, NULL, NULL, NULL, NULL);

    DwmExtendFrameIntoClientArea(Overlay, &Margin);
    SetWindowLong(Overlay, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
    ShowWindow(Overlay, SW_SHOW);
    UpdateWindow(Overlay);
}

void InitD3d()
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
    {
        exit(4);
    }

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.BackBufferWidth = ProcessWindowWidth;
    d3dpp.BackBufferHeight = ProcessWindowHeight;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.hDeviceWindow = Overlay;
    d3dpp.Windowed = TRUE;

    p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Overlay, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 14, NULL, io.Fonts->GetGlyphRangesJapanese());
    io.IniFilename = NULL;

    ImGui_ImplWin32_Init(Overlay);
    ImGui_ImplDX9_Init(D3dDevice);

    ImGui::StyleColorsDark();
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
}