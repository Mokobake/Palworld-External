#pragma once

namespace Offsets
{
	uintptr_t UWorld = NULL;
	uintptr_t PersistentLevel = NULL;
	uintptr_t WorldSettings = NULL;
	uintptr_t OwningGameInstance = NULL;
	uintptr_t LocalPlayers = NULL;
	uintptr_t GameSetting = NULL;
	uintptr_t PlayerController = NULL;
	uintptr_t ViewportClient = NULL;
	uintptr_t PlayerState = NULL;
	uintptr_t InventoryData = NULL;
	uintptr_t AcknowledgedPawn = NULL;
	uintptr_t RootComponent = NULL;
	uintptr_t Mesh = NULL;
	uintptr_t CharacterMovement = NULL;
	uintptr_t CharacterParameterComponent = NULL;
	uintptr_t OtomoPal = NULL;
	uintptr_t IndividualParameter = NULL;
	uintptr_t FollowCamera = NULL;
	uintptr_t MyHUD = NULL;
	uintptr_t PlayerCameraManager = NULL;

	uintptr_t ComponentLocation = NULL;
	uintptr_t ControlRotation = NULL;
	uintptr_t MovementMode = NULL;
	uintptr_t CustomTimeDilation = NULL;
	uintptr_t bIsEnableMuteki = NULL;
	uintptr_t SaveParameter = NULL;
	uintptr_t HungerType = NULL;
	uintptr_t SP = NULL;
	uintptr_t bOnlyRelevantToOwner = NULL;
	uintptr_t TimeDilation = NULL;
	uintptr_t DefaultFOV = NULL;
	uintptr_t bLostFocusPaused = NULL;
	uintptr_t AspectRatio = NULL;
	uintptr_t bConstrainAspectRatio = NULL;
	uintptr_t RelativeRotation = NULL;
	uintptr_t bComponentToWorldUpdated = NULL;
	uintptr_t RelativeScale3D = NULL;
	uintptr_t CraftSpeed = NULL;
	uintptr_t Level = NULL;
	uintptr_t MaxInventoryWeight = NULL;
	uintptr_t WorldmapUIMaskClearSize = NULL;

	void SetOffsets(std::string Version)
	{
		if (Version == "0.1.2.0")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC94;
		}
		else if (Version == "0.1.3.0")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC94;
		}
		else if (Version == "0.1.3.0 2")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC94;
		}
		else if (Version == "0.1.4.0")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC9C;
		}
		else if (Version == "0.1.4.1")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC9C;
		}
		else if (Version == "0.1.4.1 2")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC9C;
		}
		else if (Version == "0.1.5.0")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC9C;
		}
		else if (Version == "0.1.5.1")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x540;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x270;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x154;
			WorldmapUIMaskClearSize = 0xC9C;
		}
		else if (Version == "0.2.4.0")
		{
			UWorld = PatternScan("\x48\x8B\x05\x00\x00\x00\x00\xEB\x05", "xxx????xx");
			PersistentLevel = 0x30;
			WorldSettings = 0x298;
			OwningGameInstance = 0x1B8;
			LocalPlayers = 0x38;
			GameSetting = 0x3C8;
			PlayerController = 0x30;
			ViewportClient = 0x78;
			PlayerState = 0x298;
			InventoryData = 0x548;
			AcknowledgedPawn = 0x338;
			RootComponent = 0x198;
			Mesh = 0x318;
			CharacterMovement = 0x320;
			CharacterParameterComponent = 0x628;
			OtomoPal = 0xF0;
			IndividualParameter = 0x108;
			FollowCamera = 0x650;
			MyHUD = 0x340;
			PlayerCameraManager = 0x348;

			ComponentLocation = 0x260;
			ControlRotation = 0x308;
			MovementMode = 0x1A4;
			CustomTimeDilation = 0x64;
			bIsEnableMuteki = 0xA2;
			SaveParameter = 0x2A0;
			HungerType = 0x128;
			SP = 0x2F0;
			bOnlyRelevantToOwner = 0x58;
			TimeDilation = 0x3C8;
			DefaultFOV = 0x2A8;
			bLostFocusPaused = 0x298;
			AspectRatio = 0x2B0;
			bConstrainAspectRatio = 0x2B4;
			RelativeRotation = 0x140;
			bComponentToWorldUpdated = 0x188;
			RelativeScale3D = 0x158;
			CraftSpeed = 0xF4;
			Level = 0x20;
			MaxInventoryWeight = 0x164;
			WorldmapUIMaskClearSize = 0xCF4;
		}
	}
}