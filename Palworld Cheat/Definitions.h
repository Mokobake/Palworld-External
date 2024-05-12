#pragma once

HWND ProcessWindow = NULL;
int ProcessID = NULL;
HANDLE ProcessHandle = NULL;
uintptr_t ProcessBaseAddress = NULL;
RECT ProcessWindowRect = { NULL };
int ProcessWindowWidth = NULL;
int ProcessWindowHeight = NULL;
int ProcessWindowCenterX = NULL;
int ProcessWindowCenterY = NULL;

HWND Overlay = NULL;
IDirect3D9Ex* p_Object = NULL;
LPDIRECT3DDEVICE9 D3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;
D3DPRESENT_PARAMETERS d3dpp = { NULL };
MARGINS Margin = { -1 };
MSG Message = { NULL };

bool Menu = true;

namespace Settings
{
    namespace Player
    {
        bool TeleportTab = false;

        bool Flight = false;
        float FlightSpeed = 10;

        bool SpeedChanger = false;
        float Speed = 2;

        bool GodMode = false;

        int CraftSpeed = 1000;

        int Level = 100;

        float MaxWeight = 1000;

        bool AntiHunger = false;

        bool InfiniteStamina = false;

        bool DisableGetCurrentLocation = false;
    }

    namespace World
    {
        bool SpeedChanger = false;
        float Speed = 2;
    }

    namespace Visual
    {
        bool FOVChanger = false;
        float FOV = 130;

        bool UnrealEngineDebugHUD = false;

        bool AspectRatioChanger = false;
        float AspectRatio = 2.5;

        bool Spinbot = false;
        float SpinSpeed = 50;

        bool FullBright = false;
    }

    namespace FriendPal
    {
        bool SizeChanger = false;
        float Size = 5;

        bool SpeedChanger = false;
        float Speed = 10;
    }
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Vector3
{
public:
    Vector3() : x(0.f), y(0.f), z(0.f)
    {

    }

    Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
    {

    }
    ~Vector3()
    {

    }

    double x;
    double y;
    double z;

    inline double Dot(Vector3 v)
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline double Distance(Vector3 v)
    {
        return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
    }

    Vector3 operator+(Vector3 v)
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(Vector3 v)
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(double number)
    {
        return Vector3(x * number, y * number, z * number);
    }

    bool operator==(Vector3 v)
    {
        if (x == v.x && y == v.y && z == v.z)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    double Length()
    {
        return sqrt((x * x) + (y * y) + (z * z));
    }
};