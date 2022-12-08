// Copyright Soumik Bhattacherjee All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LaserChessGameTarget : TargetRules
{
	public LaserChessGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LaserChessGame" } );
	}
}
