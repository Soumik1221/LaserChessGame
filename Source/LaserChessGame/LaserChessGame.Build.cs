// Copyright Soumik Bhattacherjee All Rights Reserved.

using UnrealBuildTool;

public class LaserChessGame : ModuleRules
{
	public LaserChessGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
	}
}
