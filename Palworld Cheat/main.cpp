#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <array>
#include <d3d9.h>
#include <dwmapi.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "Dwmapi.lib")

#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_win32.h"
#include "ImGui/backends/imgui_impl_dx9.h"
#include "Definitions.h"
#include "Utils.h"
#include "Offsets.h"

void Loop()
{
	system("cls");
	std::cout << "\n  Started.\n";

	static RECT CachedProcessWindowRect;
	ZeroMemory(&Message, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&Message, ProcessWindow, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND ActiveWindow = GetForegroundWindow();
		if (ActiveWindow == ProcessWindow)
		{
			HWND hwnd = GetWindow(ActiveWindow, GW_HWNDPREV);
			SetWindowPos(Overlay, hwnd, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (GetAsyncKeyState(VK_END))
		{
			exit(5);
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			Menu = !Menu;
		}

		ProcessWindow = FindWindow(L"UnrealWindow", L"Pal  ");

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = Overlay;
		io.DeltaTime = 1.0f / 60.0f;

		POINT xy;
		ZeroMemory(&xy, sizeof(POINT));
		ClientToScreen(ProcessWindow, &xy);

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
		{
			io.MouseDown[0] = false;
		}

		if (ProcessWindowRect.left != CachedProcessWindowRect.left || ProcessWindowRect.right != CachedProcessWindowRect.right || ProcessWindowRect.top != CachedProcessWindowRect.top || ProcessWindowRect.bottom != CachedProcessWindowRect.bottom)
		{
			CachedProcessWindowRect = ProcessWindowRect;

			d3dpp.BackBufferWidth = ProcessWindowWidth;
			d3dpp.BackBufferHeight = ProcessWindowHeight;
			D3dDevice->Reset(&d3dpp);
		}

		uintptr_t UWorld = read<uintptr_t>(Offsets::UWorld);
		uintptr_t PersistentLevel = read<uintptr_t>(UWorld + Offsets::PersistentLevel);
		uintptr_t WorldSettings = read<uintptr_t>(PersistentLevel + Offsets::WorldSettings);
		uintptr_t OwningGameInstance = read<uintptr_t>(UWorld + Offsets::OwningGameInstance);
		uintptr_t LocalPlayer = read<uintptr_t>(read<uintptr_t>(OwningGameInstance + Offsets::LocalPlayers));
		uintptr_t GameSetting = read<uintptr_t>(OwningGameInstance + Offsets::GameSetting);
		uintptr_t PlayerController = read<uintptr_t>(LocalPlayer + Offsets::PlayerController);
		uintptr_t ViewportClient = read<uintptr_t>(LocalPlayer + Offsets::ViewportClient);
		uintptr_t PlayerState = read<uintptr_t>(PlayerController + Offsets::PlayerState);
		uintptr_t InventoryData = read<uintptr_t>(PlayerState + Offsets::InventoryData);
		uintptr_t AcknowledgedPawn = read<uintptr_t>(PlayerController + Offsets::AcknowledgedPawn);
		uintptr_t RootComponent = read<uintptr_t>(AcknowledgedPawn + Offsets::RootComponent);
		uintptr_t Mesh = read<uintptr_t>(AcknowledgedPawn + Offsets::Mesh);
		uintptr_t CharacterMovement = read<uintptr_t>(AcknowledgedPawn + Offsets::CharacterMovement);
		uintptr_t CharacterParameterComponent = read<uintptr_t>(AcknowledgedPawn + Offsets::CharacterParameterComponent);
		uintptr_t OtomoPal = read<uintptr_t>(CharacterParameterComponent + Offsets::OtomoPal);
		uintptr_t OtomoPalMesh = read<uintptr_t>(OtomoPal + Offsets::Mesh);
		uintptr_t IndividualParameter = read<uintptr_t>(CharacterParameterComponent + Offsets::IndividualParameter);
		uintptr_t FollowCamera = read<uintptr_t>(AcknowledgedPawn + Offsets::FollowCamera);
		uintptr_t MyHUD = read<uintptr_t>(PlayerController + Offsets::MyHUD);
		uintptr_t PlayerCameraManager = read<uintptr_t>(PlayerController + Offsets::PlayerCameraManager);

		//uintptr_t NickName = read<uintptr_t>(IndividualParameter + 0x270 + 0x40);
		//int Length = read<int>(IndividualParameter + 0x270 + 0x40 + sizeof(uintptr_t));
		//wchar_t* NameBuffer = new wchar_t[Length];
		//read(NickName, NameBuffer, (Length * 2));
		//std::wcout << NameBuffer << std::endl;

		//Vector3 CameraLocation = read<Vector3>(read<uintptr_t>(UWorld + 0x110));
		//printf("%f, %f, %f\n", CameraLocation.x, CameraLocation.y, CameraLocation.z);

		//for (int i = 0; i < read<int>(PersistentLevel + 0x98 + sizeof(uintptr_t)); i++)
		//{
		//	uintptr_t Actors = read<uintptr_t>(PersistentLevel + 0x98);
		//	uintptr_t AActor = read<uintptr_t>(Actors + i * sizeof(uintptr_t));
		//	if (AActor != AcknowledgedPawn)
		//	{
		//		write<float>(AActor + 0x64, 1);
		//	}
		//}

		if (Settings::Player::Flight)
		{
			Vector3 ComponentLocation = read<Vector3>(RootComponent + Offsets::ComponentLocation);
			Vector3 ControlRotation = read<Vector3>(PlayerController + Offsets::ControlRotation);
			bool pushing;

			if (GetAsyncKeyState('W'))
			{
				pushing = true;
			}
			else if (GetAsyncKeyState('S'))
			{
				ControlRotation = { -ControlRotation.x, ControlRotation.y + 180, 0 };
				pushing = true;
			}
			else if (GetAsyncKeyState('A'))
			{
				ControlRotation = { 0, ControlRotation.y + 270, 0 };
				pushing = true;
			}
			else if (GetAsyncKeyState('D'))
			{
				ControlRotation = { 0, ControlRotation.y + 90, 0 };
				pushing = true;
			}
			else
			{
				pushing = false;
			}

			double angle;

			angle = ControlRotation.y * (3.14159265358979323846 / 180.0);
			double sy = sinf(angle);
			double cy = cosf(angle);

			angle = -ControlRotation.x * (3.14159265358979323846 / 180.0);
			double sp = sinf(angle);
			double cp = cosf(angle);

			if (pushing)
			{
				ComponentLocation = Vector3(ComponentLocation + Vector3{ cp * cy , cp * sy, -sp } *Settings::Player::FlightSpeed);
			}

			write<Vector3>(RootComponent + Offsets::ComponentLocation, ComponentLocation);
			write<uint8_t>(CharacterMovement + Offsets::MovementMode, 5);
		}
		else if (read<uint8_t>(CharacterMovement + Offsets::MovementMode) == 5)
		{
			write<uint8_t>(CharacterMovement + Offsets::MovementMode, 1);
		}

		if (Settings::Player::SpeedChanger)
		{
			write<float>(AcknowledgedPawn + Offsets::CustomTimeDilation, Settings::Player::Speed);
		}
		else if (read<float>(AcknowledgedPawn + Offsets::CustomTimeDilation) == Settings::Player::Speed)
		{
			write<float>(AcknowledgedPawn + Offsets::CustomTimeDilation, 1);
		}

		if (Settings::Player::GodMode)
		{
			write<bool>(CharacterParameterComponent + Offsets::bIsEnableMuteki, true);
		}
		else if (read<bool>(CharacterParameterComponent + Offsets::bIsEnableMuteki) == true)
		{
			write<bool>(CharacterParameterComponent + Offsets::bIsEnableMuteki, false);
		}

		if (Settings::Player::AntiHunger)
		{
			write<uint8_t>(IndividualParameter + Offsets::SaveParameter + Offsets::HungerType, 0);
		}

		if (Settings::Player::InfiniteStamina)
		{
			write<int64_t>(CharacterParameterComponent + Offsets::SP, 1000000);
		}

		if (Settings::Player::DisableGetCurrentLocation)
		{
			write<char>(AcknowledgedPawn + Offsets::bOnlyRelevantToOwner, 0);
		}
		else if (read<char>(AcknowledgedPawn + Offsets::bOnlyRelevantToOwner) == 0)
		{
			write<char>(AcknowledgedPawn + Offsets::bOnlyRelevantToOwner, 0x30);
		}


		if (Settings::World::SpeedChanger)
		{
			write<float>(WorldSettings + Offsets::TimeDilation, Settings::World::Speed);
		}
		else if (read<float>(WorldSettings + Offsets::TimeDilation) == Settings::World::Speed)
		{
			write<float>(WorldSettings + Offsets::TimeDilation, 1);
		}


		if (Settings::Visual::FOVChanger)
		{
			write<float>(PlayerCameraManager + Offsets::DefaultFOV + 0x4, Settings::Visual::FOV);
		}
		else if (read<float>(PlayerCameraManager + Offsets::DefaultFOV + 0x4) == Settings::Visual::FOV)
		{
			write<float>(PlayerCameraManager + Offsets::DefaultFOV + 0x4, 0);
		}

		if (Settings::Visual::UnrealEngineDebugHUD)
		{
			write<char>(MyHUD + Offsets::bLostFocusPaused, -1);
		}
		else if (read<char>(MyHUD + Offsets::bLostFocusPaused) == -1)
		{
			write<char>(MyHUD + Offsets::bLostFocusPaused, 3);
		}

		if (Settings::Visual::AspectRatioChanger)
		{
			write<float>(FollowCamera + Offsets::AspectRatio, Settings::Visual::AspectRatio);
			write<char>(FollowCamera + Offsets::bConstrainAspectRatio, -1);
		}
		else if (read<float>(FollowCamera + Offsets::AspectRatio) == Settings::Visual::AspectRatio && read<char>(FollowCamera + Offsets::bConstrainAspectRatio) == -1)
		{
			write<float>(FollowCamera + Offsets::AspectRatio, 1.778);
			write<char>(FollowCamera + Offsets::bConstrainAspectRatio, 0);
		}

		static Vector3 Rotation = Vector3(0, 0, 0);
		if (Settings::Visual::Spinbot)
		{
			Rotation.y += Settings::Visual::SpinSpeed;
			write<Vector3>(Mesh + Offsets::RelativeRotation, Rotation);
			write<char>(Mesh + Offsets::bComponentToWorldUpdated, 0x30);
		}
		else if (read<Vector3>(Mesh + Offsets::RelativeRotation) == Rotation)
		{
			write<Vector3>(Mesh + Offsets::RelativeRotation, Vector3(0, -90, 0));
		}

		if (Settings::Visual::FullBright)
		{
			write<char>(ViewportClient + 0xB0, 1);
		}
		else if (read<char>(ViewportClient + 0xB0) == 1)
		{
			write<char>(ViewportClient + 0xB0, 3);
		}


		if (Settings::FriendPal::SizeChanger)
		{
			write<Vector3>(OtomoPalMesh + Offsets::RelativeScale3D, Vector3(Settings::FriendPal::Size, Settings::FriendPal::Size, Settings::FriendPal::Size));
		}
		else if (read<Vector3>(OtomoPalMesh + Offsets::RelativeScale3D) == Vector3(Settings::FriendPal::Size, Settings::FriendPal::Size, Settings::FriendPal::Size))
		{
			write<Vector3>(OtomoPalMesh + Offsets::RelativeScale3D, Vector3(1, 1, 1));
		}

		if (Settings::FriendPal::SpeedChanger)
		{
			write<float>(OtomoPal + Offsets::CustomTimeDilation, Settings::FriendPal::Speed);
		}
		else if (read<float>(OtomoPal + Offsets::CustomTimeDilation) == Settings::FriendPal::Speed)
		{
			write<float>(OtomoPal + Offsets::CustomTimeDilation, 1);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (Menu)
		{
			ImGui::SetNextWindowSize({ 600, 300 });
			ImGui::Begin("Palworld Cheat (BETA)", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			ImGui::BeginTabBar("TabBar");
			if (ImGui::BeginTabItem("Player"))
			{
				ImGui::Checkbox("Teleport Tab", &Settings::Player::TeleportTab);

				if (Settings::Player::TeleportTab)
				{
					ImGui::SetNextWindowSize({ 300, 800 });
					ImGui::Begin("Teleport", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

					if (ImGui::Button("Plateau of Beginnings"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-358959, 268084, 7997));
					}
					
					if (ImGui::Button("Grassy Behemoth Hills"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-341858, 236998, -1668));
					}
					
					if (ImGui::Button("Rayne Syndicate Tower Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-317957, 212206, -672));
					}

					if (ImGui::Button("Tower of the Rayne Syndicate"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-321717, 208983, 6757));
					}

					if (ImGui::Button("Fort Ruins"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-302884, 241233, -999));
					}

					if (ImGui::Button("Desolate Church"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-315034, 186728, 3358));
					}

					if (ImGui::Button("Small Settlement"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-346824, 191656, -218));
					}

					if (ImGui::Button("Sealed Realm of the Frozen Wings"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-278314, 212573, -806));
					}

					if (ImGui::Button("Islandhopper Coast"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-266057, 268866, -1869));
					}

					if (ImGui::Button("Marsh Island"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-282302, 355569, -1861));
					}

					if (ImGui::Button("Bridge of the Twin Knights"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-295024, 152273, 277));
					}

					if (ImGui::Button("Ravine Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-318926, 127384, -1958));
					}

					if (ImGui::Button("Sealed Realm of the Swordmaster"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-338419, 107820, -1294));
					}

					if (ImGui::Button("Small Cove"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-374256, 63787, -1794));
					}

					if (ImGui::Button("Sea Breeze Archipelago Church"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-376684, 124817, 2390));
					}

					if (ImGui::Button("Sea Breeze Archipelago Castaway Beach"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-450506, 112604, -1986));
					}

					if (ImGui::Button("Ascetic Falls"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-326530, 55270, 6971));
					}

					if (ImGui::Button("Sealed Realm of the Thunder Dragon"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-283794, 59153, 5398));
					}

					if (ImGui::Button("Ancient Ritual Site"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-258138, 151228, 123));
					}

					if (ImGui::Button("Cinnamoth Forest"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-248865, 126030, 5955));
					}

					if (ImGui::Button("Lake Center"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-221393, 164975, 31));
					}

					if (ImGui::Button("Hypocrite Hill"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-237410, 190611, 4060));
					}

					if (ImGui::Button("Mount Flopie Summit"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-167867, 167590, 9265));
					}

					if (ImGui::Button("Gobfin's Turf"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-219019, 226257, -1859));
					}

					if (ImGui::Button("Mossanda Forest"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-177973, 265042, 955));
					}

					if (ImGui::Button("Sealed Realm of the Swift"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-115648, 289136, 3123));
					}

					if (ImGui::Button("Sealed Realm of the Guardian"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-151968, 213138, 3400));
					}

					if (ImGui::Button("Snowy Mountain Fork"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-125466, 201717, 6977));
					}

					if (ImGui::Button("Free Pal Alliance Tower Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-103345, 234942, 19528));
					}

					if (ImGui::Button("Tower of the Free Pal Alliance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-109971, 241455, 25622));
					}

					if (ImGui::Button("Eastern Wild Island"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-170838, 409870, 4139));
					}

					if (ImGui::Button("Investigator's Fork"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-218842, 58413, 3779));
					}

					if (ImGui::Button("Sealed Realm of the Winged Tyrant"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-195118, 36825, 8396));
					}

					if (ImGui::Button("Deep Bamboo Thicket"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-215547, 8955, 13248));
					}

					if (ImGui::Button("Azurobe Hill"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-170211, -29277, -1850));
					}

					if (ImGui::Button("Forgotten Island"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-137222, -91497, -1990));
					}

					if (ImGui::Button("Forgotten Island Church Ruins"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-129907, -53364, 1805));
					}

					if (ImGui::Button("Ice Wind Island"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-88757, -3758, -778));
					}

					if (ImGui::Button("Cold Shore"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-119212, 138359, -1156));
					}

					if (ImGui::Button("No Man's Trail"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-80660, 141348, 8194));
					}

					if (ImGui::Button("Icy Weasel Hill"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-39586, 159631, 17067));
					}

					if (ImGui::Button("Unthawable Lake"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(7875, 111903, 2651));
					}

					if (ImGui::Button("Pristine Snow Field"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(117, 135, 6686));
					}

					if (ImGui::Button("PAL Genetic Research Unit Tower Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(89777, 94460, 67400));
					}

					if (ImGui::Button("Tower of the PAL Genetic Research Unit"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(81240, 90112, 70598));
					}

					if (ImGui::Button("Land of Absolute Zero"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(102006, 48591, 28485));
					}

					if (ImGui::Button("Sand Dunes Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-50463, 287329, 353));
					}

					if (ImGui::Button("Duneshelter"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(35436, 321384, 714));
					}

					if (ImGui::Button("PIDF Tower Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(29740, 406770, 15752));
					}

					if (ImGui::Button("Tower of the PIDF"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(29734, 413317, 22316));
					}

					if (ImGui::Button("Deep Sand Dunes"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(117542, 400004, -1839));
					}

					if (ImGui::Button("Ancient Civilization Ruins"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-414501, -24456, 3633));
					}

					if (ImGui::Button("Fisherman's Point"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-465742, -62219, -1753));
					}

					if (ImGui::Button("Mount Obsidian Anubis Statue"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-416683, -89878, 23400));
					}

					if (ImGui::Button("Eternal Pyre Tower Entrance"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-367622, -114820, 61466));
					}

					if (ImGui::Button("Tower of the Brothers of the Eternal Pyre"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-361792, -111948, 68010));
					}

					if (ImGui::Button("Mount Obsidian Midpoint"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-327473, -70269, 19060));
					}

					if (ImGui::Button("Foot of the Volcano"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-349445, -3906, 951));
					}

					if (ImGui::Button("Ruined Fortress City"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-236852, -99903, 611));
					}

					if (ImGui::Button("Beach of Everlasting Summer"))
					{
						write<Vector3>(RootComponent + Offsets::ComponentLocation, Vector3(-383218, -210940, 922));
					}

					ImGui::End();
				}

				ImGui::Checkbox("Flight", &Settings::Player::Flight);
				ImGui::SliderFloat("Flight Speed", &Settings::Player::FlightSpeed, 0.1, 1000);

				ImGui::Checkbox("Speed Changer", &Settings::Player::SpeedChanger);
				ImGui::SliderFloat("Speed", &Settings::Player::Speed, 0.1, 100);

				ImGui::Checkbox("God Mode (from pal attacks only)", &Settings::Player::GodMode);

				ImGui::SliderInt("Craft Speed Changer", &Settings::Player::CraftSpeed, 1, 100000);
				if (ImGui::Button("Set Craft Speed"))
				{
					write<int32_t>(IndividualParameter + Offsets::SaveParameter + Offsets::CraftSpeed, Settings::Player::CraftSpeed);
				}

				ImGui::SliderInt("Level Changer", &Settings::Player::Level, 1, 100);
				if (ImGui::Button("Set Level"))
				{
					write<int32_t>(IndividualParameter + Offsets::SaveParameter + Offsets::Level, Settings::Player::Level);
				}

				ImGui::SliderFloat("Max Weight Changer", &Settings::Player::MaxWeight, 1, 10000);
				if (ImGui::Button("Set Max Weight"))
				{
					write<float>(InventoryData + Offsets::MaxInventoryWeight, Settings::Player::MaxWeight);
				}

				ImGui::Checkbox("Anti Hunger", &Settings::Player::AntiHunger);
				
				ImGui::Checkbox("Infinite Stamina", &Settings::Player::InfiniteStamina);

				ImGui::Checkbox("Disable Get Current Location", &Settings::Player::DisableGetCurrentLocation);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("World"))
			{
				ImGui::Checkbox("Speed Changer", &Settings::World::SpeedChanger);
				ImGui::SliderFloat("Speed", &Settings::World::Speed, 0.1, 100);

				if (ImGui::Button("Unlock Map (Rejoin World | thanks CrazyShoot)"))
				{
					write<float>(GameSetting + Offsets::WorldmapUIMaskClearSize, 9999);
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Visual"))
			{
				ImGui::Checkbox("FOV Changer", &Settings::Visual::FOVChanger);
				ImGui::SliderFloat("FOV", &Settings::Visual::FOV, 0.1, 170);

				ImGui::Checkbox("Unreal Engine Debug HUD", &Settings::Visual::UnrealEngineDebugHUD);

				ImGui::Checkbox("Aspect Ratio Changer", &Settings::Visual::AspectRatioChanger);
				ImGui::SliderFloat("Aspect Ratio", &Settings::Visual::AspectRatio, 0.1, 100);

				ImGui::Checkbox("Spinbot", &Settings::Visual::Spinbot);
				ImGui::SliderFloat("Spin Speed", &Settings::Visual::SpinSpeed, -50, 50);

				ImGui::Checkbox("Full Bright (thanks Nknights23)", &Settings::Visual::FullBright);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Friend Pal"))
			{
				ImGui::Checkbox("Size Changer", &Settings::FriendPal::SizeChanger);
				ImGui::SliderFloat("Size", &Settings::FriendPal::Size, 0.1, 100);

				ImGui::Checkbox("Speed Changer", &Settings::FriendPal::SpeedChanger);
				ImGui::SliderFloat("Speed", &Settings::FriendPal::Speed, 0.1, 100);

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();

			ImGui::End();

			//write<char>(PlayerController + 0x544, -1);
		}
		else if (read<char>(PlayerController + 0x544) == -1)
		{
			//write<char>(PlayerController + 0x544, 0);
		}

		ImGui::EndFrame();
		D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	
		if (D3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			D3dDevice->EndScene();
		}
	
		HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			D3dDevice->Reset(&d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	
		Sleep(1);
	}
	
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	
	DestroyWindow(Overlay);
}

int main()
{
	SetConsoleTitle(L"Palworld Cheat");
	std::cout << "\n  Launch Palworld...";
	while (!ProcessWindow)
	{
		ProcessWindow = FindWindow(L"UnrealWindow", L"Pal  ");
	}
	if (!ProcessWindow)
	{
		Error("ProcessWindow");
	}
	system("cls");
	GetProcessInfo(L"Palworld-Win64-Shipping.exe");
	if (!ProcessID)
	{
		Error("ProcessID");
	}
	if (!ProcessHandle)
	{
		Error("ProcessHandle");
	}
	if (!ProcessBaseAddress)
	{
		Error("ProcessBaseAddress");
	}

	std::cout << "\n  Welcome to Palworld Cheat.";
	std::cout << "\n  Developer: Mokobake";
	std::cout << "\n\n  WARNING!!!!!!!!!!!!!!!";
	std::cout << "\n  Do not play other online games while using this cheat as Overlay may be flagged as an Anti Cheat for other games.";
	std::cout << "\n\n  Select Palworld Version.";
	std::cout << "\n  [1] 0.1.2.0";
	std::cout << "\n  [2] 0.1.3.0";
	std::cout << "\n  [3] 0.1.3.0 2";
	std::cout << "\n  [4] 0.1.4.0";
	std::cout << "\n  [5] 0.1.4.1";
	std::cout << "\n  [6] 0.1.4.1 2";
	std::cout << "\n  [7] 0.1.5.0";
	std::cout << "\n  [8] 0.1.5.1";
	std::cout << "\n  [9] 0.2.4.0";
	std::cout << "\n  Select: ";

	std::string Version;
	int Select;
	std::cin >> Select;
	switch (Select)
	{
	case 1:
		Version = "0.1.2.0";
		break;
	case 2:
		Version = "0.1.3.0";
		break;
	case 3:
		Version = "0.1.3.0 2";
		break;
	case 4:
		Version = "0.1.4.0";
		break;
	case 5:
		Version = "0.1.4.1";
		break;
	case 6:
		Version = "0.1.4.1 2";
		break;
	case 7:
		Version = "0.1.5.0";
		break;
	case 8:
		Version = "0.1.5.1";
		break;
	case 9:
		Version = "0.2.4.0";
		break;
	}
	system("cls");
	std::cout << "\n  Starting...";

	Offsets::SetOffsets(Version);
	CreateOverlay();
	InitD3d();
	Loop();
	Shutdown();
}