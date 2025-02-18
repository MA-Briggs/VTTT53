// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VTT53 : ModuleRules
{
	public VTT53(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
   


        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","AgoraPlugin", "EnhancedInput" });
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "AndroidPermission" });
		}
		PrivateDependencyModuleNames.AddRange(new string[] {  });
    }
}
