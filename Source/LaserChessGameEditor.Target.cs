// Copyright Soumik Bhattacherjee All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LaserChessGameEditorTarget : TargetRules
{
	public LaserChessGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LaserChessGame" } );
	}
}
